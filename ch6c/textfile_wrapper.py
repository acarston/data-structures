import ctypes

# lib = ctypes.CDLL('./textfile.dll')
lib = ctypes.CDLL('C:/Users/amcar/source/repos/data_structures/textfile/x64/Release/textfile.dll')

class TextFile:
    def __init__(self) -> None:
        lib.CTextFileDefault.argtypes = [ctypes.c_void_p]
        lib.CTextFileDefault.restype = ctypes.c_void_p

        lib.c_set_input.argtypes = [ctypes.c_void_p]
        lib.c_set_input.restype = ctypes.c_void_p

        lib.c_parse_into_tree.argtypes = [ctypes.c_void_p]
        lib.c_parse_into_tree.restype = ctypes.c_void_p

        lib.c_print_words.argtypes = [ctypes.c_void_p]
        lib.c_print_words.restype = ctypes.c_void_p

        self.obj = lib.CTextFileDefault(None)

    def set_input(self, input: str, person: str) -> None:
        lib.c_set_input(self.obj, input, person)
        
    def parse_into_tree(self) -> None:
        lib.c_parse_into_tree(self.obj)

    def print_words(self, filePath: str) -> None:
        lib.c_print_words(self.obj, filePath)

def driver():
    textFile = TextFile()
    textFile.set_input('something in the way', 'Aaron')
    textFile.parse_into_tree()
    textFile.print_words('./out.txt')