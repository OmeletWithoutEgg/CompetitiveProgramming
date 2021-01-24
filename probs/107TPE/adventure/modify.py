import requests
import random
import string
from bs4 import BeautifulSoup
from getpass import *

# config

upload_input = False
upload_output = False
input_suffix = '.in'
output_suffix = '.out'
input_prefix = 'tests/'
output_prefix = 'tests/'
filename_format = '%s%02d%s' # % (prefix, id, suffix)
time_limit = '1000'
memory_limit = '524288'
output_limit = '65536'

# end config

session = requests.Session()

if upload_input or upload_output: print("You're going to replace testdatas!")

def login():
    TIOJusername = input('Username: ')
    TIOJpassword = getpass('Password: ')
    print('logging in...')
    global session
    rel = session.get('https://tioj.ck.tp.edu.tw/users/sign_in')
    soup = BeautifulSoup(rel.text, "html.parser")
    inputs = soup.find('form').find_all('input')
    rel = session.post('https://tioj.ck.tp.edu.tw/users/sign_in', data = {
        inputs[0].attrs['name']: inputs[0].attrs['value'],
        inputs[1].attrs['name']: inputs[1].attrs['value'],
        'user[username]': TIOJusername,
        'user[password]': TIOJpassword,
        'user[remember_me]': '1',
        'commit': 'Sign in'
    })

login()
print('Successful log in')
problem_id = input('Problem ID: ')
num_start = int(input('Testdata start number: '))
num_end = int(input('Testdata end number: '))

url = 'https://tioj.ck.tp.edu.tw/problems/%s/testdata' % problem_id

rel = session.get(url)
soup = BeautifulSoup(rel.text, "html.parser")
inputs = soup.find_all('a')

lst = []
for t in inputs:
    st = str(t)
    if st.find("btn btn-info btn-xs") != -1:
        c = st.find("testdata") + 9
        d = st.find("/", c)
        val = int(st[c:d])
        if not val in lst: lst.append(val)
lst = lst[num_start:num_end+1]

if len(lst) == 0: print('Error')

c = num_start
for i in lst:
    print('processing %d(%d)...' % (c, i))
    now_url = 'https://tioj.ck.tp.edu.tw/problems/%s/testdata/%d/edit' % (problem_id, i)
    post_url = now_url[:-5]

    rel = session.get(now_url)
    soup = BeautifulSoup(rel.text, "html.parser")
    inputs = soup.find('form').find_all('input')

    data = {
        inputs[0].attrs['name']: inputs[0].attrs['value'],
        inputs[1].attrs['name']: inputs[1].attrs['value'],
        inputs[2].attrs['name']: inputs[2].attrs['value'],
        'testdatum[limit_attributes][time]': time_limit,
        'testdatum[limit_attributes][memory]': memory_limit,
        'testdatum[limit_attributes][output]': output_limit,
        'testdatum[limit_attributes][id]': str(i),
        'testdatum[problem_id]': problem_id,
        'commit': 'Update Testdatum'
    }

    files = {}
    if upload_input: files['testdatum[test_input]'] = open(filename_format % (input_prefix, c, input_suffix), 'rb')
    if upload_output: files['testdatum[test_output]'] = open(filename_format % (output_prefix, c, output_suffix), 'rb')
    rel = session.post(post_url, data = data, files = files)

    print('Modify %d(%d)!!' % (c, i))
    c += 1
