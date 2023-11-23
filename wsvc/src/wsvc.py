#!/usr/bin/python3

"""
werdl wrote this code
"""
import os
import logging
import sys
import json
import pickle
import shutil
import inspect
from time import gmtime, strftime, time
import requests
import ftplib
import bs4


class wsvc():
    def __init__(self) -> None:
        """Check wsvc repo if exists, assigns to `self.init`"""
        self.init = True if os.path.exists(".wsvc") else False
        self.currentstate = ""
        for item in os.listdir():
            if item.startswith("wsvc-commit") and os.path.isdir(item):
                shutil.rmtree(item)
        with open(".wsvc/config.json", "r") as config:
            data = json.load(config)
        self.user=data["user"]
    def setuser(self,user) -> None:
        """Set the user value used for all commits"""
        self.user=user

        with open(".wsvc/config.json", "r") as config:
            data = json.load(config)
            data["user"]=user
        with open(".wsvc/config.json", "w") as config:
            config.write(json.dumps(data))
    def create(self, reponame: str, latestname: str="latest",force=False) -> bool:
        """Initialize wsvc repo (name `reponame`)at `savedir`, overwriting if `force`"""
        if not os.path.exists(".wsvc"):
            os.makedirs(".wsvc")
        else:
            if force:
                logging.warning("Over-writing existing directory")
            else:
                logging.error("Path not created, dir already exists")
                sys.exit(-1)
        with open(".wsvc/config.json", "w") as config:
            data = json.dumps({"name": reponame, "created": strftime("%Y-%m-%d %H:%M:%S", gmtime()),"latestmsg":latestname,"user":self.user})
            config.write(data)
        return 1
    def check(self) -> bool:
        """Check if wsvc exists in folder"""
        return self.init

    def serialize(self) -> bool:
        """Serialize current repo into a string"""
        if not self.init:
            return False

        tempserial = {}

        for dirpath, dirnames, filenames in os.walk("."):
            if ".wsvc" in dirpath.split(os.sep):
                continue
            for file in filenames:
                file_path = os.path.join(dirpath, file)
                with open(file_path) as f:
                    content = f.read()
                    tempserial[file_path] = content
        self.currentstate = pickle.dumps(tempserial).hex() + ":" + pickle.dumps(self.user).hex()
        return 1

    def stash(self, commitmsg) -> bool:
        """Stashes changes away under name `commitmsg` 
        Returns if successful"""
        if not os.path.exists(".wsvc"):
            os.makedirs(".wsvc")
        with open(".wsvc/{0}-{1}.wsvccommit".format(round(time()), commitmsg), "w") as file:
            file.write(self.currentstate)
        print("Changes stashed")

    def grab(self, commit,dir="wsvc-commit"):
        """Grab commit `commit`"""
        files = next(os.walk(".wsvc"), (None, None, []))[2]
        commit_directory = f"wsvc-commit-{commit}" if dir=="wsvc-commit" else "."
        if dir!="wsvc-commit":
            print("Overwriting current directory, -r/--restore flag given.")
        potentials = {}
        for file in files:
            if ".wsvccommit" in file:
                pass
            else:
                continue
            _temp = file.split("-")
            name = _temp[1].split(".")[0]
            ts = _temp[0]
            if name == commit:
                potentials[file] = ts
        sortedpots = sorted(potentials.items(), key=lambda item: item[1])
        match len(sortedpots):
            case 0:
                print(f"No matches found for commit {commit}")
                return
            case 1:
                print(f"Exactly 1 match found")
            case _:
                print(f"Multiple matches found. Selecting last commit.")
        with open(".wsvc/" + sortedpots[-1][0]) as f:
            contents = f.read().replace("\n", "")
            filecontent=contents.split(":")[0]
            file_contents = pickle.loads(bytes.fromhex(filecontent))
            print(f"This commit, which was created on {str((sortedpots[-1][0])).split('-')[1]} is authored by  {(bytes.fromhex(contents.split(':')[1])).decode(encoding='utf-8', errors='ignore')}") # grab data from the file
        for file_path, value in file_contents.items():
            file_directory, file_name = os.path.split(file_path)
            file_directory = os.path.join(commit_directory, file_directory)
            if not os.path.exists(file_directory):
                os.makedirs(file_directory)

            # If the value is an empty string, create an empty file
            if not value:
                open(os.path.join(file_directory, file_name), "w").close()
            else:
                with open(os.path.join(file_directory, file_name), "w") as f:
                    f.write(value)
        return True
    def help(self,function) -> str:
        """Helps info on function `function`"""
        classobj=wsvc()
        method=getattr(classobj,function,None)
        if inspect.ismethod(method):
            method_source = inspect.getsource(method)
            method_lines = method_source.strip().split('\n')
            method_definition_line = method_lines[0].strip()
            return f"""{method_definition_line}
    - {method.__doc__}"""
        else:
            return f"{function} is not a valid wsvc operation"
    def delete(self):
        shutil.rmtree(".wsvc")
    def push_remote(self):
        with open(".wsvc/credentials.json") as c:
            con=c.read()
            content=json.loads(con)
        self.set_remote(content["server"], content["dir"], content["user"], content["pass"])
    def pull(self):
        with open(".wsvc/credentials.json") as c:
            con=c.read()
            content=json.loads(con)
        url=f"https://{content['server']}/{content['dir']+'/' if content['dir']!='public_html' else ''}wsvc"
        print(url)
        r = requests.get(url)
        data = bs4.BeautifulSoup(r.text, "html.parser")
        for l in data.find_all("a"):
            r = requests.get(url + l["href"])

            with open(f".wsvc/{l['href']}", "w") as file:
                file.write(r.text)


    def set_remote(self, addr, dirr, user, password):
        with open(".wsvc/credentials.json", "w") as conf:
            out={
                "server": addr,
                "user": user,
                "pass": password,
                "dir": dirr
            }
            conf.write(json.dumps(out))
        session = ftplib.FTP(out["server"],out["user"],out["pass"])
        for root, _, files in os.walk('.wsvc'):
            for fname in files:
                if fname.split(".")[1]=="wsvccommit" or fname.split(".")[1]=="json":
                    session.storbinary(f'STOR {dirr}/wsvc/{fname}.wsvc', open(".wsvc/"+fname
, 'rb'))  
class wsvcException(Exception):
    def __init__(self,msg):
        self.msg=msg
    def __str__(self):
        return self.msg
    
def err(reqlength=2):
    """Returns if sys.argv isn't long enough"""
    if len(sys.argv)<reqlength+1:
        raise wsvcException("sys.argv too short")

instance = wsvc()
if len(sys.argv) > 1:
    action = sys.argv[1]
    if action == "init":
        err()
        if len(sys.argv)<4:
            instance.create(reponame=sys.argv[2], force=False)
        else:
            instance.create(reponame=sys.argv[2], force=False,latestname=sys.argv[3])
    elif action == "del":
        instance.delete()
    elif action == "check":
        print("Exists:", instance.check())
    elif action == "stash":
        err()
        instance.serialize()
        instance.stash(sys.argv[2])
    elif action == "grab":
        err()
        if len(sys.argv)>3:
            if sys.argv[3]=="-r" or sys.argv[3]=="--restore":
                instance.grab(sys.argv[2],".")
            else:
                instance.grab(sys.argv[2])
        else:
            instance.grab(sys.argv[2])
    elif action=="help":
        if len(sys.argv)>2:
            print(instance.help(sys.argv[2]))
        else:
            print("""
# init - create new repo
- required: reponame
- optional: latestname (name of commit usually 'latest')

# del - delete repo
- required: None
- optional: None

# check - check repo existence
- required: None
- optional: None

# stash - stash changes
- required: commitname
- optional: None

# grab - grab changes
- required: commitname
- optional: -r/--restore flag (overwrites cwd)

# help - print this page
- required: None
- optional: funcname (help for a specific function)

# push - stash under latest
required: None
optional: commitname for duplicate

# setuser - set the current user (by default 'anon')
required: user
optional: None
""")
    elif action=="push":
        instance.serialize()
        with open(".wsvc/config.json") as config:
            instance.stash(json.loads(config.read())["latestmsg"])
        if len(sys.argv)>2:
            instance.stash(sys.argv[2])
    elif action=="setuser":
        err()
        instance.setuser(sys.argv[2])
    elif action=="pushrem":
        instance.push_remote()
    elif action=="pull":
        instance.pull()
    elif action=="setrem":
        err(5)
        instance.set_remote(sys.argv[2],sys.argv[3],sys.argv[4],sys.argv[5])
    else:
        print("Invalid action")
else:
    print("No action specified")
