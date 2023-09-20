import makpy, sys
@makpy.makpy("hey")
def MyFunction():
    print("MyFunction triggered!")

if sys.argv[1] in makpy.runtime():
    exec(f"{makpy.runtime()[sys.argv[1]]}()")
