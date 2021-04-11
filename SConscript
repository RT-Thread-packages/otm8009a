from building import *
Import('rtconfig')

src   = []
cwd   = GetCurrentDir()

# add otm8009a src files.
if GetDepend('PKG_USING_OTM8009A'):
    src += Glob('src/otm8009a.c')

# add otm8009a include path.
path  = [cwd + '/inc']

# add src and include to group.
group = DefineGroup('otm8009a', src, depend = ['PKG_USING_OTM8009A'], CPPPATH = path)

Return('group')
