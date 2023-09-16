from math import sqrt
import re
class equation:
    def __init__(self):
        self.currtotal=0
        self.ops=[]
        self.eq=""
        self.validsigns=["+","-","/","*","**"]
        self.replacements={
            "x": "*",
            "^": "**",
            "÷": "/"
        }
    def digit(self,num: int):
        self.eq+=str(num)
    def op(self,sign):
        if sign in self.validsigns:
            self.eq+=sign
        elif sign in self.replacements.keys():
            self.eq+=self.replacements[sign]
        else:
            raise Exception("Invalid sign!")
    def brack(self,lr):
        self.eq+=(("*" if self.eq[-1].isnumeric() else "")+"(") if lr=="l" else ")"
    def nthroot(self,base,n):
        self.eq+=f"{base}**(1/{n})"
    def __str__(self):
        print(self.eq)
        print(eval(self.eq))
        return f"{self.eq}->{eval(self.eq)}"

eq=equation()
eq.digit(2)
eq.op("^")
eq.digit(3)
print(eq)