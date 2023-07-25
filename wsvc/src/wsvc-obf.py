import os
import logging
import sys
import json
import pickle
import shutil
import inspect
from time import gmtime, strftime, time
class IlIIlIIIIlIllIIIIll():
    def __init__(lIllllIIlIllllllIl) -> None:
        lIllllIIlIllllllIl.lIlllIIlIllllIll = True if os.path.exists(".wsvc") else False
        lIllllIIlIllllllIl.llIlIllIlIll = ""
        for lIlllIII in os.listdir():
            if lIlllIII.startswith("wsvc-commit") and os.path.isdir(lIlllIII):
                shutil.rmtree(lIlllIII)
    def IIlIlIIllIIllIlIIllI(lIllllIIlIllllllIl, llllllIlIIlIIlllIlI: str, IIllllII: str="latest",IIlIlIIIIIIIlIIIIl=False) -> bool:
        if not os.path.exists(".wsvc"):
            os.makedirs(".wsvc")
        else:
            if IIlIlIIIIIIIlIIIIl:
                logging.warning("Over-writing existing directory")
            else:
                logging.error("Path not created, dir already exists")
                sys.exit(-1)
        with open(".wsvc/config.json", "w") as IlIIllllllIIlllIlIlI:
            IlllllllIlIIllllIlll = json.dumps({"name": llllllIlIIlIIlllIlI, "created": strftime("%Y-%m-%d %H:%M:%S", gmtime()),"latestmsg":IIllllII})
            IlIIllllllIIlllIlIlI.write(IlllllllIlIIllllIlll)
        return 1
    def IllllIIIIIIllIlIll(lIllllIIlIllllllIl) -> bool:
        return lIllllIIlIllllllIl.lIlllIIlIllllIll
    def IIllllllIlIllIlllI(lIllllIIlIllllllIl) -> bool:
        if not lIllllIIlIllllllIl.lIlllIIlIllllIll:
            return False
        lIIlllIIllIllllIl = {}
        for IIIIlIIIlI, lIlIIIIIII, IllIIIlIII in os.walk("."):
            if ".wsvc" in IIIIlIIIlI.split(os.sep):
                continue
            for IllIIIlllllIlIlII in IllIIIlIII:
                lIlIIlIIIIllllIlI = os.path.join(IIIIlIIIlI, IllIIIlllllIlIlII)
                with open(lIlIIlIIIIllllIlI) as llllIlIlIII:
                    lIlIIlllIIl = llllIlIlIII.read()
                    lIIlllIIllIllllIl[lIlIIlIIIIllllIlI] = lIlIIlllIIl
        lIllllIIlIllllllIl.llIlIllIlIll = pickle.dumps(lIIlllIIllIllllIl).hex()
        return 1
    def lIIIIIIlIIIlIlI(lIllllIIlIllllllIl, IlIlIlllIlll) -> bool:
        if not os.path.exists(".wsvc"):
            os.makedirs(".wsvc")
        with open(".wsvc/{0}-{1}.wsvccommit".format(round(time()), IlIlIlllIlll), "w") as IllIIIlllllIlIlII:
            IllIIIlllllIlIlII.write(lIllllIIlIllllllIl.llIlIllIlIll)
        print("Changes stashed")
    def lllIllIIllIl(lIllllIIlIllllllIl, IllIIlIIIlIIIlII,IIIIIIllIllIlllllIlI="wsvc-commit"):
        lIllIIlI = next(os.walk(".wsvc"), (None, None, []))[2]
        IllIIlllIllIIIIllIII = llllIlIlIII"wsvc-commit-{IllIIlIIIlIIIlII}" if IIIIIIllIllIlllllIlI=="wsvc-commit" else "."
        if IIIIIIllIllIlllllIlI!="wsvc-commit":
            print("Overwriting current directory, -r/--restore flag given.")
        IlIlIlllllIIlllllIII = {}
        print(lIllIIlI)
        for IllIIIlllllIlIlII in lIllIIlI:
            if ".wsvccommit" in IllIIIlllllIlIlII:
                pass
            else:
                continue
            llIIlIII = IllIIIlllllIlIlII.split("-")
            IIlIlllIllIIIIlIII = llIIlIII[1].split(".")[0]
            llIllllIlIIllIIl = llIIlIII[0]
            if IIlIlllIllIIIIlIII == IllIIlIIIlIIIlII:
                IlIlIlllllIIlllllIII[IllIIIlllllIlIlII] = llIllllIlIIllIIl
        lIIIlIIlllIlIIlllll = sorted(IlIlIlllllIIlllllIII.items(), key=lambda lIlllIII: lIlllIII[1])
        match len(lIIIlIIlllIlIIlllll):
            case 0:
                print(llllIlIlIII"No matches found for commit {IllIIlIIIlIIIlII}")
                return
            case 1:
                print(llllIlIlIII"Exactly 1 match found")
            case _:
                print(llllIlIlIII"Multiple matches found. Selecting last commit.")
        with open(".wsvc/" + lIIIlIIlllIlIIlllll[-1][0]) as llllIlIlIII:
            lIllIllllllIIIIl = llllIlIlIII.read().replace("\n", "")
            lIIlIIlllllIIlIIl = pickle.loads(bytes.fromhex(lIllIllllllIIIIl))
        for lIlIIlIIIIllllIlI, lllIIllllIIllIIIl in lIIlIIlllllIIlIIl.items():
            lIIIlIIlIIIlIII, lllllIllllIIllI = os.path.split(lIlIIlIIIIllllIlI)
            lIIIlIIlIIIlIII = os.path.join(IllIIlllIllIIIIllIII, lIIIlIIlIIIlIII)
            if not os.path.exists(lIIIlIIlIIIlIII):
                os.makedirs(lIIIlIIlIIIlIII)
            if not lllIIllllIIllIIIl:
                open(os.path.join(lIIIlIIlIIIlIII, lllllIllllIIllI), "w").close()
            else:
                with open(os.path.join(lIIIlIIlIIIlIII, lllllIllllIIllI), "w") as llllIlIlIII:
                    llllIlIlIII.write(lllIIllllIIllIIIl)
        return True
    def IlIlIIIllllll(lIllllIIlIllllllIl,IllIIlIIIIlIIllIIllI) -> str:
        IllIlIllIlIIlllIIlIl=IlIIlIIIIlIllIIIIll()
        IIlIIIllllIllIIllIl=getattr(IllIlIllIlIIlllIIlIl,IllIIlIIIIlIIllIIllI,None)
        if inspect.ismethod(IIlIIIllllIllIIllIl):
            IIllIlIll = inspect.getsource(IIlIIIllllIllIIllIl)
            IIIllllIl = IIllIlIll.strip().split('\n')
            IlIIIlIlIIlIIllI = IIIllllIl[0].strip()
            return llllIlIlIII"""{IlIIIlIlIIlIIllI}
    - {IIlIIIllllIllIIllIl.__doc__}"""
        else:
            return llllIlIlIII"{IllIIlIIIIlIIllIIllI} is not a valid wsvc operation"
    def IIlIlIIlllIllII(lIllllIIlIllllllIl):
        shutil.rmtree(".wsvc")
class IlIIllIIllIllI(Exception):
    def __init__(lIllllIIlIllllllIl,lIlIIIlIllllIIl):
        lIllllIIlIllllllIl.lIlIIIlIllllIIl=lIlIIIlIllllIIl
    def IllIllIIlll(lIllllIIlIllllllIl):
        return lIllllIIlIllllllIl.lIlIIIlIllllIIl
def IIIlIIIII(IIIllIIllllIIIIIl=2):
    if len(sys.argv)<IIIllIIllllIIIIIl+1:
        raise IlIIllIIllIllI("sys.argv too short")
IlIllIlIlllIllIlI = IlIIlIIIIlIllIIIIll()
if len(sys.argv) > 1:
    llIlllIllIIlIIll = sys.argv[1]
    if llIlllIllIIlIIll == "init":
        IIIlIIIII()
        if len(sys.argv)<4:
            IlIllIlIlllIllIlI.IIlIlIIllIIllIlIIllI(llllllIlIIlIIlllIlI=sys.argv[2], IIlIlIIIIIIIlIIIIl=False)
        else:
            IlIllIlIlllIllIlI.IIlIlIIllIIllIlIIllI(llllllIlIIlIIlllIlI=sys.argv[2], IIlIlIIIIIIIlIIIIl=False,IIllllII=sys.argv[3])
    elif llIlllIllIIlIIll == "del":
        IlIllIlIlllIllIlI.IIlIlIIlllIllII()
    elif llIlllIllIIlIIll == "check":
        print("Exists:", IlIllIlIlllIllIlI.IllllIIIIIIllIlIll())
    elif llIlllIllIIlIIll == "stash":
        IIIlIIIII()
        IlIllIlIlllIllIlI.IIllllllIlIllIlllI()
        IlIllIlIlllIllIlI.lIIIIIIlIIIlIlI(sys.argv[2])
    elif llIlllIllIIlIIll == "grab":
        IIIlIIIII()
        if len(sys.argv)>3:
            if sys.argv[3]=="-r" or sys.argv[3]=="--restore":
                IlIllIlIlllIllIlI.lllIllIIllIl(sys.argv[2],".")
            else:
                IlIllIlIlllIllIlI.lllIllIIllIl(sys.argv[2])
        else:
            IlIllIlIlllIllIlI.lllIllIIllIl(sys.argv[2])
    elif llIlllIllIIlIIll=="help":
        if len(sys.argv)>2:
            print(IlIllIlIlllIllIlI.IlIlIIIllllll(sys.argv[2]))
        else:
            print("""
# lIlllIIlIllllIll - IIlIlIIllIIllIlIIllI new repo
- required: llllllIlIIlIIlllIlI
- optional: IIllllII (IIlIlllIllIIIIlIII of IllIIlIIIlIIIlII usually 'latest')
# del - IIlIlIIlllIllII repo
- required: None
- optional: None
# IllllIIIIIIllIlIll - IllllIIIIIIllIlIll repo existence
- required: None
- optional: None
# lIIIIIIlIIIlIlI - lIIIIIIlIIIlIlI changes
- required: commitname
- optional: None
# lllIllIIllIl - lllIllIIllIl changes
- required: commitname
- optional: -r/--restore flag (overwrites cwd)
# IlIlIIIllllll - print this page
- required: None
- optional: funcname (IlIlIIIllllll for a specific IllIIlIIIIlIIllIIllI)
# push - lIIIIIIlIIIlIlI under latest
required: None
optional: commitname for duplicate
""")
    elif llIlllIllIIlIIll=="push":
        IlIllIlIlllIllIlI.IIllllllIlIllIlllI()
        with open(".wsvc/config.json") as IlIIllllllIIlllIlIlI:
            IlIllIlIlllIllIlI.lIIIIIIlIIIlIlI(json.loads(IlIIllllllIIlllIlIlI.read())["latestmsg"])
        if len(sys.argv)>2:
            IlIllIlIlllIllIlI.lIIIIIIlIIIlIlI(sys.argv[2])
    else:
        print("Invalid action")
else:
    print("No action specified")