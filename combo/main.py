keyboard = {
    '2':'abc',
    '3':'def',
    '4':'ghi',
    '5':'jkl',
    '6':'mno',
    '7':'pqrs',
    '8':'tuv',
    '9':'wxyz'
}

def back(x, res):
    if not x:
        print(res, end=' ')
        return
    for i in x[0]:
        back(x[1::], res + i)
    
if __name__ == '__main__':
    inp = [keyboard[i] for i in input()]
    back(inp, '')