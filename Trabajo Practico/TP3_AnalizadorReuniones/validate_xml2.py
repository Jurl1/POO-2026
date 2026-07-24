import re

stack = []
widget_stack = []
with open('mainwindow.ui', 'r', encoding='utf-8') as f:
    for i, line in enumerate(f, 1):
        tags = re.findall(r'<(/)?([a-zA-Z0-9_]+)[^>]*?(/)?>', line)
        for is_end, name, is_self_closing in tags:
            if is_self_closing or name == 'xml' or name == 'string': continue
            if is_end:
                if stack and stack[-1] == name:
                    stack.pop()
                    if name == 'widget': 
                        w = widget_stack.pop()
                        if 510 <= i <= 520: print(f'Line {i}: closed widget {w}')
                else:
                    exit(1)
            else:
                stack.append(name)
                if name == 'widget':
                    m = re.search(r'name=\"([^\"]+)\"', line)
                    wname = m.group(1) if m else 'unknown'
                    widget_stack.append(wname)
