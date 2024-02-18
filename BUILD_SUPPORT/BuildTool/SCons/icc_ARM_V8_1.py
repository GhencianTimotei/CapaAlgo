import os
from SCons.Tool import Tool, createProgBuilder, createObjBuilders
from utilities import SilentTempFileMunge
from SCons.Script import Builder
import SCons.Defaults
import SCons.Tool
import SCons.Util

ASSuffixes = ['.s']

def configureAssembler(env):
    a_assembler = Tool('as')
    a_assembler(env)

    env['AS'] = 'iasmarm.exe'
    env['ASCOM']     = '$AS -o $TARGET $SOURCES $ASFLAGS'
    
def configureCompiler(env):
    
    c_compiler = Tool('cc')
    c_compiler(env)
    root_dir = os.getcwd()
    
    # Add include paths for IAR compiler
    for dir_name in env['APPL_INCLUDES']:
        dir_name=dir_name.replace('/','\\')
        dir_name = dir_name[2:]
        dir_abs_path = '\"'+ dir_name + '\"'
        env.Append(CCFLAGS='-I '+ dir_abs_path)

    env['CC'] = 'iccarm.exe'
    env['CCCOM']     = '$CC -o $TARGET $SOURCES $CCFLAGS'
  
    
def configureLinker(env):
    linker = Tool('link')
    linker(env)
    env['LINK'] = 'ilinkarm.exe'   
    env['TEMPFILE'] = SilentTempFileMunge
    env['LINKCOM'] = '$LINK -o $TARGET $LINKER_FILE $LINKFLAGS'

    def add_unused_symbol(env, symbols):
        for symbol in symbols:
            env.Append(LINKFLAGS='-u %s' % symbol)    
    env.AddMethod(add_unused_symbol, 'AddForceKeep')

def generate(env):
    compiler_path = '' 
    env['TEMPFILEPREFIX'] = '-@'

    if os.environ.has_key('COMPILER_PATH'):
        compiler_path = os.environ['COMPILER_PATH']
    else:
        print 'No environment variable COMPILER_PATH was detected'
        sys.exit(1)    

    env.AppendENVPath('PATH', compiler_path)  

    configureCompiler(env)
    configureAssembler(env)
    configureLinker(env)
    createProgBuilder(env)

def exists(env):
    return True
