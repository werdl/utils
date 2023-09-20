import json, sys, os
def makpy(alias):
    def decorator(function):
        with open(".makpy",'a+') as file:
            try:
                file_data = json.load(file)
            except json.JSONDecodeError:
                file_data={}
            file_data[alias]=function.__name__
            json.dump(file_data, file, indent = 4)
            def wrapper(*args, **kwargs):
                result = function(*args, **kwargs)
                return result
            return wrapper
    return decorator

def runtime():
    with open(".makpy",'w+') as file:
        try:
            file_data = json.load(file)
        except json.JSONDecodeError:
            file_data={}
    # os.remove(".makpy")
    return file_data