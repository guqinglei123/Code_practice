from notion.client import NotionClient

# Obtain the `token_v2` value by inspecting your browser cookies on a logged-in session on Notion.so
client = NotionClient(token_v2="f3049f356cdeadf3bd79469b68ac607601e4e0a93c896141d08822f8fe66f32ac0221eb3fc8a23b8379a88e44d8235b03986cf1bef06173f68f660339d9ce4d456dc364d0710b6cbb143d8c35504")

# Replace this URL with the URL of the page you want to edit
page = client.get_block("https://www.notion.so/ea647d55c7e44676ba14af610233a335")

print("The old title is:", page.title)

# Note: You can use Markdown! We convert on-the-fly to Notion's internal formatted text data structure.
page.title = "The title has now changed, and has *live-updated* in the browser!"