import re

stack = []
with open('mainwindow.ui', 'r', encoding='utf-8') as f:
    for i, line in enumerate(f, 1):
        tags = re.findall(r'<(/)?([a-zA-Z0-9_]+)[^>]*?(/)?>', line)
        for is_end, name, is_self_closing in tags:
            if is_self_closing or name == 'xml' or name == 'string': continue
            if is_end:
                if stack and stack[-1] == name:
                    stack.pop()
                    if i > 650: print(f'Line {i}: closed {name}')
                else:
                    print(f'Line {i}: trying to close {name}, but stack top is {stack[-1] if stack else "empty"}')
                    print(f'  Stack: {stack}')
                    exit(1)
            else:
                stack.append(name)
                if i > 650: print(f'Line {i}: opened {name}')
