# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

import tempfile
import shutil
import sys

def before_scenario(context, scenario):
	context.tmpdir = tempfile.mkdtemp()


def after_scenario(context, scenario):
	if hasattr(context, 'brightnessd'):
		if context.brightnessd.poll() is None:
			context.brightnessd.terminate()
			context.brightnessd.wait()

	shutil.rmtree(context.tmpdir)


