#
# A simple Evernote API demo script that lists all notebooks in the user's
# account and creates a simple test note in the default notebook.
#
# Before running this sample, you must fill in your Evernote developer token.
#
# To run (Unix):
#   export PYTHONPATH=../../lib; python EDAMTest.py
#
import json, os, time, sys, re
import hashlib 
import binascii
import evernote.edam.userstore.constants as UserStoreConstants
import evernote.edam.type.ttypes as Types
import evernote.edam.notestore.NoteStore as NoteStore
from os.path import join, exists

from evernote.api.client import EvernoteClient

# Real applications authenticate with Evernote using OAuth, but for the
# purpose of exploring the API, you can get a developer token that allows
# you to access your own Evernote account. To get a developer token, visit
# https://sandbox.evernote.com/api/DeveloperToken.action
auth_token = "S=s542:U=9396ac7:E=16a922a8b90:C=1633a795bf0:P=1cd:A=en-devtoken:V=2:H=a52d36ceee1fbb574a2f8ccf2bada4e3"

if auth_token == "your developer token":
    print("Please fill in your developer token")
    print("To get a developer token, visit " \
          "https://sandbox.evernote.com/api/DeveloperToken.action")
    exit(1)

# Initial development is performed on our sandbox server. To use the production
# service, change sandbox=False and replace your
# developer token above with a token from
# https://www.evernote.com/api/DeveloperToken.action
# To access Sandbox service, set sandbox to True
# To access production (International) service, set both sandbox and china to False
# To access production (China) service, set sandbox to False and china to True

sandbox=False
china=False

client = EvernoteClient(token=auth_token, sandbox=sandbox,china=china)

##获得用户类，通过该类可以获得用户信息
user_store = client.get_user_store()
version_ok = user_store.checkVersion(
    "Evernote EDAMTest (Python)",
    UserStoreConstants.EDAM_VERSION_MAJOR,
    UserStoreConstants.EDAM_VERSION_MINOR
)
# print("Is my Evernote API version up to date? ", str(version_ok))
if not version_ok:
    exit(1)
print(' {} 登陆成功'.format(user_store.getUser().username))
upload_limit=  {
            1: 25 * 1024 * 1024,
            3: 100 * 1024 * 1024,
            5: 200 * 1024 * 1024,
        }.get(user_store.getUser().privilege, 0)
print('你的上传限制为：',upload_limit);

# 获得笔记本仓库类，得到该用户下所有笔记本信息，包括创建、删除笔记、笔记本
# List all of the notebooks in the user's account
note_store = client.get_note_store()
notebooks = note_store.listNotebooks()
print("Found ", len(notebooks), " notebooks.")
for notebook in notebooks:
    print(" *{0:30}:  {1}".format(notebook.name,notebook.guid))


# 选取一个笔记本，然后读取笔记本中所有笔记信息
f = NoteStore.NoteFilter()
s = NoteStore.NotesMetadataResultSpec()
s.includeTitle = True
s.includeUpdated = True 
notebookGuid = note_store.listNotebooks()[0].guid
f.notebookGuid = notebookGuid
noteFullPath="E:\\Code_practice\\Python_Practice\\evernote2md\\testdata\\"
for note in note_store.findNotesMetadata( f, 0, 9999,s).notes:
    attachmentDict = {}
    for resource in (note_store.getNote(note.guid, False, True, False, False).resources or {}):
        attachmentDict[resource.attributes.fileName] = resource.data.body
    contentDict = attachmentDict
    r = note_store.getNoteContent(note.guid)
    content = re.compile('[\s\S]*?<en-note[^>]*?>([\s\S]*?)</en-note>').findall(r)[0]
    contentDict[note.title+'.html'] = content
    def make_path(p):
        if os.path.exists(p):       # 判断文件夹是否存在
            os.rmdir(p)        # 删除文件夹
        os.mkdir(p)                 # 创建文件夹
    mediapath = noteFullPath + "media\\"
    make_path(mediapath)
    contentDict2 = {}
    contentDict2 = contentDict
    
    # if len(contentDict) == 1:
    #     for k, v in contentDict2.items():
    #         attachmentspath = mediapath +k
    #         with open(attachmentspath+[k], 'wb') as f: f.write(v)
    # else:
    #     for k, v in contentDict2.iteritems():
    #         with open(mediapath+[k], 'wb') as f: f.write(v)
    # open(noteFullPath+note.title+".html","w", buffering=-1, encoding="utf-8").write(content)
    # attachmentDict[noteFullPath+'.html'] = content
    # for k, v in attachmentDict.items():
    #     if k == None:
    #         continue
    #     else:
    #         pass
    #     print(k);
    #     attachmentspath = mediapath +k
    #     # print(type(mediapath),type(v))
    #     with open(attachmentspath, 'wb') as f: f.write(v)

# 创建一个新笔记
# print()
# print("Creating a new note in the default notebook")
# print()

# # To create a new note, simply create a new Note object and fill in
# # attributes such as the note's title.
# note = Types.Note()
# note.title = "Test note from EDAMTest.py"

# # To include an attachment such as an image in a note, first create a Resource
# # for the attachment. At a minimum, the Resource contains the binary attachment
# # data, an MD5 hash of the binary data, and the attachment MIME type.
# # It can also include attributes such as filename and location.
# image_path = constants_path = os.path.join(os.path.dirname(__file__), "enlogo.png")
# with open(image_path, 'rb') as image_file:
#     image = image_file.read()
# md5 = hashlib.md5()
# md5.update(image)
# hash = md5.digest()

# data = Types.Data()
# data.size = len(image)
# data.bodyHash = hash
# data.body = image

# resource = Types.Resource()
# resource.mime = 'image/png'
# resource.data = data

# # Now, add the new Resource to the note's list of resources
# note.resources = [resource]

# # To display the Resource as part of the note's content, include an <en-media>
# # tag in the note's ENML content. The en-media tag identifies the corresponding
# # Resource using the MD5 hash.
# hash_hex = binascii.hexlify(hash)
# hash_str = hash_hex.decode("UTF-8")

# # The content of an Evernote note is represented using Evernote Markup Language
# # (ENML). The full ENML specification can be found in the Evernote API Overview
# # at http://dev.evernote.com/documentation/cloud/chapters/ENML.php
# note.content = '<?xml version="1.0" encoding="UTF-8"?>'
# note.content += '<!DOCTYPE en-note SYSTEM ' \
#                 '"http://xml.evernote.com/pub/enml2.dtd">'
# note.content += '<en-note>Here is the Evernote logo:<br/>'
# note.content += '<en-media type="image/png" hash="{}"/>'.format(hash_str)
# note.content += '</en-note>'

# # Finally, send the new note to Evernote using the createNote method
# # The new Note object that is returned will contain server-generated
# # attributes such as the new note's unique GUID.
# created_note = note_store.createNote(note)

# print("Successfully created a new note with GUID: ", created_note.guid)