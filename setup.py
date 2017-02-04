from distutils.core import setup, Extension

spam = Extension('spam', sources = ['krakenmodule.c'])

setup (name = 'PackageName', version = '0.1',
        description = 'This is a demo package',
        ext_modules = [spam])

