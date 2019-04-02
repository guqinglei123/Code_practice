
import html2text as ht  # pip install html2text
import os 
text_maker = ht.HTML2Text()
text_maker.ignore_links = True
text_maker.bypass_tables = True
path ="E:\\Code_practice\\Python_Practice\\evernote2md\\testdata\\1.html"
htmlfile = open(path,'r',encoding='UTF-8')
htmlpage = htmlfile.read()
text = text_maker.handle(htmlpage)
text2 = text.replace('\[','['); 
text3 = text2.replace('\]',']'); 
# md = text.split('#')  # split post content
open("E:\\Code_practice\\Python_Practice\\evernote2md\\testdata\\1.md","w", buffering=-1, encoding="utf-8").write(text3)  # write file as a md file