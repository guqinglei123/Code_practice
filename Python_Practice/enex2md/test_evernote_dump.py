import unittest
import os
import shutil
from evernote_dump import run_parse


class TestEvernoteDump(unittest.TestCase):

    def test_run_parse_single_file_with_out_overwrite(self):
        run_parse(['Archives.enex'])
        self.assertTrue(os.path.isdir('Archives'))
        shutil.rmtree('Archives')

    def test_run_parse_auto_rename_do_not_overwrite(self):
        run_parse(['Check It Out.enex', ])
        run_parse(['Check It Out.enex', ])
        self.assertTrue(os.path.isdir('Check It Out'))
        self.assertTrue(os.path.isfile('Check It Out\\Great Chili-2.md'))
        shutil.rmtree('Check It Out')

    def test_run_parse_multiple_files(self):
        run_parse(['Archives.enex', 'Recipes.enex'])
        # self.assertTrue(os.path.isdir('Archives'))
        # self.assertTrue(os.path.isdir('Recipes'))
        # shutil.rmtree('Archives')
        # shutil.rmtree('Recipes')

    def test_run_parse_with_spaces_in_file_name(self):
        run_parse(['Check It Out.enex', ])
        self.assertTrue(os.path.isdir('Check It Out'))
        shutil.rmtree('Check It Out')

testEvernote = TestEvernoteDump()
testEvernote.test_run_parse_multiple_files()
# if __name__ == '__main__':
#     unittest.main()
