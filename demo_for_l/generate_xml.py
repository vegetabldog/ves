import xml.etree.ElementTree as ET

with open('a.txt', 'r') as f:
    s = f.read()
    items = s.split('\n')
    items = [item for item in items if len(item)]

root_name, sroot, k1, v1, save_name = items

root = ET.Element(root_name)
country = ET.SubElement(root, sroot, {k1: v1})
tree = ET.ElementTree(root)
tree.write(save_name)
