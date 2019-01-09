import os
import sys

def daemon(nochdir=False, noclose=False):
    'Enter into daemon mode'
    pid = os.fork()
    if pid < 0:
        return -1
    if pid != 0:
        sys.exit(0)
    os.setsid()
    if nochdir == False:
        os.chdir('/')
    os.umask(0)
    if noclose == False:
        pass
    return 0
