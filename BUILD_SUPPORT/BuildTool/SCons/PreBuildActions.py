import sys, os
from subprocess import Popen, PIPE, STDOUT

# ----------- MAIN Function -----------
def main(lst, args):   
    
    boolean = True
    
    if "all" in args:
        boolean = PathChecks(lst)
    
    if ("all" in args or "version_check" in args) and (boolean==True):
        boolean = CheckThatCompilerVersionIsOK(lst)
        
    print "Done with PreBuild actions."
    return boolean 
# --------- end MAIN


# 1. Verify Compiler version
def CheckThatCompilerVersionIsOK( lst ):

    CompilerName = lst[0]
    CompilerCommand = lst[1]
    CompilerVersion = lst[2]
    # Check chesscc version number
    boolean = False
    for dir in os.environ['COMPILER_PATH'].split(os.pathsep):
        dir = dir.replace("\"","")
        if os.path.isdir(dir):
            compiler = os.path.join(dir , CompilerName)
            if (os.path.isfile(compiler)):
                try:
                    p = Popen( compiler + CompilerCommand , cwd=r".", stdout=PIPE ,stderr = STDOUT)
                    stdout, stderr = p.communicate()
                    var=stdout.find("IAR ANSI C/C++ Compiler")
                    if "License check failed" in  stdout:
                        print "\n Build Error: \n License check failed. Use the IAR License Manager to resolve the problem. \n "
                        return False
                    elif CompilerVersion not in stdout:
                        print "\n Build Error: wrong compiler version"
                        print " Project configured: " + CompilerVersion                        
                        print " Used compiler version: " +  stdout[var:var+28].rstrip() + "\n"
                        return False
                    else:
                        print " -->> Compiler version is correct! \n"
                        boolean = True
                except WindowsError:
                    print " Compiler version verification failed! \n Please check in build.bat file >> COMPILER_PATH variable \nMake sure your path is added. "
    return boolean

# 2. Paths check
def PathChecks(lst):
    CompilerName = lst[0]
    CompilerCommand = lst[1]
    CompilerVersion = lst[2]
    
    print "COMPILER_PATH from build.bat is:"
    boolean = False
    for dir in os.environ['COMPILER_PATH'].split(os.pathsep):
        dir = dir.replace("\"","")
        print dir
        if os.path.isdir(dir):
            compiler = os.path.join(dir , CompilerName)
            if (os.path.isfile(compiler)):
                print "  Compiler Location on this machine is: " + compiler
                boolean = True

    if not boolean:
        print "Compiler not Found on this machine at any COMPILER_PATH! "
        
    return boolean


# 3. calculate *.xcl
def Source_Calculation():
    obj_list = []
    
    if (os.path.isfile("build.bat")):
        try:
            p = Popen( "python scons/scons.py -Q --site-dir scons/site_scons -n --tree=derived", cwd=r".", stdout=PIPE ,stderr = STDOUT)
            stdout, stderr = p.communicate()
            lines = stdout.split("\n")
    
            for lin in lines:
                lin = lin.replace("+-","").strip()
                if ".o" in lin and "ilinkrl78" not in lin and "iccrl78.exe" not in lin and "iasmrl78.exe" not in lin and ".out" not in lin and not "org.apache" in lin:
                    if lin not in obj_list:
                        obj_list.append(os.path.basename(lin))
                        
        except WindowsError:
             print " Something went wrong in computing the *.xcl file "
             
    else: print "The build.bat file does not exist!"

    if obj_list:
        try: 
            with open("..\..\ProjectSettings\linklist.xcl",'r') as linlist:
                link_list= linlist.readlines()
                for obj in obj_list:
                    flag = False
                    if any(obj in s for s in link_list):
                       flag = True
                    if flag == False:
                       print "WARNING !!! The following object file: "+ obj + " is missing from the ProjectSettings\linklist.xcl !\n\n"
        except WindowsError:
             print " Something went wrong in computing the *.xcl file "

def checkSconcripts(inputFile, list):
    
    with open(inputFile, 'r') as myFile:
        fileContent = myFile.read()
        for fileName in list:
            if (os.path.basename(fileName).lower() not in fileContent) and (os.path.basename(fileName) not in fileContent) and\
			   (os.path.basename(fileName).lower() not in fileContent.lower()):
                print 'Warning! The file ' + os.path.basename(fileName) + ' does not exist in the ' + inputFile + '\n'

#Check if each module has a Build\Source\Sconscript file
#Check if the Sconscript Files are up-to-date                 
def CheckBuildFiles(root):
    
    if not os.path.isdir(root):
        
        print 'The folder ' + root + ' does not exist or is incorrect!'
    
    else:
    
        for root,dirs,_ in os.walk(root):
            
            for dir in dirs:  
                if 'BUILD_SUPPORT' not in os.path.join(root,dir):          
                    if 'Source' in dir:
                        
                        currentFolder = os.path.dirname(os.path.join(root,dir))
                        
                        cFiles = []
                        existCFile = False

                        for file in os.listdir(os.path.join(root,dir)):
                                
                            #Save all the C Files from each module
                            if os.path.isfile(os.path.join(os.path.join(root,dir),file)) and file.endswith('.c'):

                                existCFile = True
                                cFiles.append(os.path.join(os.path.join(root,dir),file))  

                        if existCFile:                            
                            #check if the Buil\SCons folder exist
                            if os.path.isdir(currentFolder + '\\Build\Scons'):  
                                if os.path.isfile(currentFolder + '\\Build\Scons\Sconscript'):
                                    
                                    #check if the Sconscript file is up-to-date
                                    checkSconcripts(currentFolder+'\\Build\Scons\Sconscript', cFiles)

                                else: print 'The Sconscript file for the module ' + currentFolder + '\\Build\Scons does not exist!'
                            else: print 'The Build\Scons folder for the module ' +  currentFolder + ' does not exist!'


if __name__ == "__main__":
    main(sys.argv[1:])
