# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

import os
import tempfile
import shutil
import sys

def before_scenario(context, scenario):
	context.tmpdir = tempfile.mkdtemp()
	os.chdir(context.tmpdir)


def after_scenario(context, scenario):
	if hasattr(context, 'application'):
		context.application.terminate()
		context.application.wait()

	os.chdir('/')
	shutil.rmtree(context.tmpdir)


