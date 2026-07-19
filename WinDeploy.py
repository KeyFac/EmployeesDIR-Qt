import os
import subprocess
def openFile():
    with open('curVersion.txt', 'r') as f:
        content = f.read()
        global lstv
        lstv = content.split('.')
        #print(ver)
        f.close()

    
print('''
Input 'yes' or 'y' to deploy & pack the program.
Input 'back' or 'b' to minus the revision number.
Input 'read' or 'r' to see the current version number.
Input 'set' or 's' to set the version directly.
''')
c = input()
if c == "y" or c== "yes":
    openFile()
    #print(lstv)
    lstv[3] = str(int(lstv[3])+1)
    ver = "{}.{}.{}.{}".format(lstv[0],lstv[1],lstv[2],lstv[3])
    with open('curVersion.txt','w') as f:
        f.write(ver)
        f.close()
    #os.system("cd WinReleaseBins&&windeployqt EmployeesDIR.exe")
    #process = subprocess.Popen('C:\\Windows\\System32\\cmd.exe /c "copy /Y build-EmployeesDIR-Desktop_Qt_5_15_2_MinGW_64_bit-Release\\EmployeesDIR.exe WinReleaseBins\\EmployeesDIR.exe"&&"windeployqt WinReleaseBins/EmployeesDIR.exe"', stdout=subprocess.PIPE)
    process = subprocess.Popen('C:\\Windows\\System32\\cmd.exe /c windep.bat', stdout=subprocess.PIPE)
    output, error = process.communicate()
    print(output.decode('gbk'))
    if not (error is None):
        print(error.decode('gbk'))
    #os.system("windep.bat")
elif c=="b" or c=="back":
    openFile()
    lstv[3] = str(int(lstv[3])-1)
    ver = "{}.{}.{}.{}".format(lstv[0],lstv[1],lstv[2],lstv[3])
    with open('curVersion.txt','w') as f:
        f.write(ver)
        f.close()
elif c=="r" or c == "read":
    openFile()
    ver = "{}.{}.{}.{}".format(lstv[0],lstv[1],lstv[2],lstv[3])
    print(ver)
elif c == "set" or c=="s":
    ver=input()
    with open('curVersion.txt','w') as f:
        f.write(ver)
        f.close()
else:
    print("Wrong input!")

try:
    print("Program ended.\nCurrent Version:{}".format(ver))
except Exception as e:
    print("Program ended.",e)
print("Press Enter to continue...",end="")
input()
