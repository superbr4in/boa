def get_types(*args):
    result = ''
    for arg in args:
        result += str(type(arg))
    return result
