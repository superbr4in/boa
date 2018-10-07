def get_types(*args):
    result = ''
    for arg in args:
        result += str(type(arg))
    return result

def procedure():
    x = 0

def procedure_args(*args):
    for arg in args:
        x = 0

def reflect(x):
    return x

def result_bytes():
    return b''
