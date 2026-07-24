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
                    if 470 <= i <= 520:
                        print(f'Line {i}: {"  " * len(stack)}</{name}>')
                else:
                    exit(1)
            else:
                if 470 <= i <= 520:
                    m = re.search(r'name=\"([^\"]+)\"', line) if name == 'widget' else None
                    wname = f' ({m.group(1)})' if m else ''
                    print(f'Line {i}: {"  " * len(stack)}<{name}{wname}>')
                stack.append(name)
