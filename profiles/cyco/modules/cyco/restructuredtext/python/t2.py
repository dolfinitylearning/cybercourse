#Python 2
import sys
# setdefaultencoding is removed during Python start. Get it back.
# See http://stackoverflow.com/questions/2276200/changing-default-encoding-of-python
reload(sys)  # Reload does the trick!
sys.setdefaultencoding('utf-8')

from docutils import nodes, core, io
