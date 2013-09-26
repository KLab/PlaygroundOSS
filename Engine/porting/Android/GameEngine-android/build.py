#!/usr/bin/env python

from __future__ import print_function
from decimal import *
from os import makedirs, path, remove
from shutil import copy2, copytree, rmtree
import argparse
import subprocess
import sys

class PlaygroundBuilder:
    _rootdir = None

    def __init__(self):
        self._rootdir = path.dirname(path.realpath(__file__))

    def getAbsPath(self, relpath):
        return path.normpath(path.join(self._rootdir, relpath))

    def decor_print(self, header, content, color):
        print('%s%s%s: %s' % (color, header, bcolors.ENDC, content))

    def makedirs(self, target_dir):
        target_abs_dir = self.getAbsPath(target_dir)
        if not path.isdir(target_abs_dir):
            makedirs(target_abs_dir)

    def rmfile(self, target_file):
        target_abs_file = self.getAbsPath(target_file)
        if path.isfile(target_abs_file):
            self.decor_print('removing file', target_file, bcolors.WARNING)
            remove(target_abs_file)

    def rmtree(self, target_dir):
        target_abs_dir = self.getAbsPath(target_dir)
        if path.isdir(target_abs_dir):
            self.decor_print('removing dir', target_dir, bcolors.WARNING)
            rmtree(target_abs_dir)

    def copytree(self, path_from, path_to):
        return self._copyentity(path_from, path_to, False)

    def copyfile(self, path_from, path_to):
        return self._copyentity(path_from, path_to, True)

    def _copyentity(self, path_from, path_to, is_file):
        from_path = self.getAbsPath(path_from)
        (from_base_path, from_leaf_path) = path.split(from_path)
        params = (from_path, self.getAbsPath(path_to+'/'+from_leaf_path))
        if is_file:
            self.decor_print('copying file', '%s -> %s' % (path_from, path_to), bcolors.OKBLUE)
            if path.exists(params[1]) and path.samefile(*params):
                print(bcolors.NOTICE+'skipped (same file)'+bcolors.ENDC)
            else:
                copy2(*params)
        else:
            self.decor_print('copying dir', '%s -> %s' % (path_from, path_to), bcolors.OKBLUE)
            if not path.exists(params[0]):
                print(bcolors.NOTICE+'skipped (origin dir not found)'+bcolors.ENDC)
            elif path.exists(params[1]) and path.samefile(*params):
                print(bcolors.NOTICE+'skipped (same dir)'+bcolors.ENDC)
            else:
                copytree(*params) 

    def build(self, project, use_luajit=False, gles_ver=Decimal('1.1'), perform_rebuild=False, is_release=False):
        if perform_rebuild:
            self.rmtree('./jni')
            self.rmtree('./src')

        self.makedirs('./jni')
        self.copytree('../jni/Android', './jni/')
        self.copyfile('../jni/Android.mk', './jni/')
        self.copyfile('../jni/Application.mk', './jni/')
        self.copytree('../jni/proxy', './jni/')
        self.copytree('../src', '.')
        self.copytree('../../../custom', './jni/')
        self.copytree('../../../include', './jni/')
        self.copytree('../../../libs', './jni/')
        self.copytree('../../../source', './jni/')
        self.copytree('../../../../%s/world' % project, './jni/UserTask/')
        self.copytree('../../../../%s/game' % project, './jni/UserTask/')

        # layouts
        self.copyfile('../GameEngine-android/res/layout/indicator.xml', './res/layout/')
        self.copyfile('../GameEngine-android/res/layout/install.xml', './res/layout/')

        # create location to put prebuilt *.a files in
        self.makedirs('./obj/local/armeabi')
        self.makedirs('./obj/local/x86')

        # FreeType2
        self.copyfile('../../../porting/FontRendering.cpp', './jni/Android/')
        self.copyfile('../../../porting/FontRendering.h', './jni/Android/')
        self.copyfile('./jni/libs/libfreetype2/obj/local/armeabi/libfreetype2.a', './obj/local/armeabi/')
        self.copyfile('./jni/libs/libfreetype2/obj/local/x86/libfreetype2.a', './obj/local/x86/')

        # libcurl
        self.rmtree('./jni/libs/curl-7.29.0')
        self.rmtree('./jni/libs/curl-7.29.0-minimal')
        self.makedirs('./jni/libs/curl-7.29.0/include')
        self.copytree('../jni/curl-7.29.0/include', './jni/libs/curl-7.29.0/include/')
        self.copyfile('../jni/curl-7.29.0/armeabi/libcurl.a', './obj/local/armeabi')
        self.copyfile('../jni/curl-7.29.0/x86/libcurl.a', './obj/local/x86')

        # file delete API
        self.copyfile('../../../porting/FileDelete.cpp', './jni/Android/')
        self.copyfile('../../../porting/FileDelete.h', './jni/Android/')

        # remove unused files (their presence could make build break)
        self.rmfile('./jni/source/Core/CKLBStream.cpp')
        self.rmfile('./jni/source/Rendering/FontSystem.cpp')
        self.rmfile('./jni/source/Scripting/CKLBScriptEnv_forCSharp.cpp')
        self.rmfile('./jni/source/Scripting/ExportListC_Likefunction.cpp')
        self.rmfile('./jni/source/UnitSystem/UnitCompiler/serverCompiler.cpp')
        self.rmfile('./jni/source/UnitSystem/CKLBUnitDefinitionServer.cpp')
        self.rmfile('./jni/source/Core/OSSencryptFile.cpp')
        self.rmfile('./jni/source/HTTP/CKLBNetAPIBasic.cpp')
        self.rmfile('./jni/UserTask/game/framework.cpp')
        self.rmfile('./jni/UserTask/game/framework.h')
        self.rmfile('./jni/UserTask/game/out.cpp')
        self.rmtree('./jni/libs/RuntimeCSharp')
        self.rmtree('./jni/libs/freeType/')
        self.rmtree('./jni/libs/libfreetype2/src/')
        self.rmtree('./jni/libs/libfreetype2/jni/')

        cmdline = ['ndk-build']
        cmdline.append('-j')
        if use_luajit:
            self.rmtree('./jni/libs/lua')
            self.makedirs('./jni/libs/luajit-2.0.1')
            self.copytree('../jni/luajit-2.0.1/include', './jni/libs/luajit-2.0.1/')
            self.copyfile('../jni/luajit-2.0.1/libluajit-5.1.a', './obj/local/armeabi')
            cmdline.append('USE_LUAJIT=1')

        if gles_ver is not Decimal('1.1'):
            if Decimal('2.0') <= gles_ver:
                cmdline.append('USE_GLES2=1')
            if Decimal('3.0') <= gles_ver:
                cmdline.append('USE_GLES3=1')

        if is_release:
            cmdline.append('NDK_DEBUG=0')
            print("performing release build")
        cmdline_s = ' '.join(cmdline)
        print('performing: %s' % (cmdline_s))
        p = subprocess.Popen(cmdline_s, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        for l in iter(p.stdout.readline, b''):
            print('%s>>%s %s' % (bcolors.OKGREEN, bcolors.ENDC, l.rstrip().decode('utf-8')))

# http://stackoverflow.com/questions/287871/print-in-terminal-with-colors-using-python
class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[91m'
    NOTICE = '\033[37m'
    ENDC = '\033[0m'

    def disable(self):
        self.HEADER = ''
        self.OKBLUE = ''
        self.OKGREEN = ''
        self.WARNING = ''
        self.FAIL = ''
        self.ENDC = ''

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Playground for Android Native Binaries Builder')
    parser.add_argument('-p', '--project', required=True)
    parser.add_argument('-l', '--luavm', choices=['lua', 'luajit'], default='lua')
    parser.add_argument('-g', '--gles', choices=['1.1', '2.0', '3.0'], default='1.1')
    parser.add_argument('-m', '--mode', choices=['debug', 'release'], default='debug')
    parser.add_argument('-r', '--rebuild', action='store_true')

    args = parser.parse_args()
    builder = PlaygroundBuilder()
    builder.build(
            project=args.project,
            use_luajit=(True if args.luavm == 'luajit' else False),
            gles_ver=Decimal(args.gles),
            perform_rebuild=args.rebuild,
            is_release=(True if args.mode == 'release' else False))
