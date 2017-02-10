# -*- coding: utf-8 -*
import requests
import urllib
from bs4 import BeautifulSoup



#判斷是好雷、普雷、負雷，必不會計算到repost的部分
def judge(title):
    global good
    global ok
    global bad
    for i in range(len(title)):
        if title[i] == '好':
            good += 1
        elif title[i] == '普':
            ok += 1
        elif title[i] == '負':
            bad += 1
        elif title[i] == ']' or title[i] == 'R':
            return
        else:
            continue
    
def find_the_target(url, target):
    global count
    global target_title
    
    #搜尋到最新的一百頁
    if count > 100:
        return
    else:
        index = 'http://www.ptt.cc'
        
        r = requests.get (url)
        html = r.content
        soup = BeautifulSoup ( html, 'html.parser')
        #get the tag of the previous page
        prev = soup.findAll ( "a" , {"class" : "btn wide"})[1]
        link = prev.get('href')

        #get the tag of the title
        tag = soup.findAll(  "a"  )

        
        list =  []
        for i in range(len(tag)):
            list.append( tag[i].contents )    

        #using judge fnt and record the title that we find
       
        for j in range(len(list)):
            temp = list[j]
            if target in temp[0]:
                judge(temp[0])
                target_title.append(temp[0])
                
        del list

        #read the previous page
        prev_page = urllib.parse.urljoin(index, link)
        count += 1
        find_the_target(prev_page, target)

        
good = 0
ok = 0
bad = 0
count = 0
target_title = []

#you can change the target_words and start_url by using input
target_words = '分裂'
start_url = 'https://www.ptt.cc/bbs/movie/index5101.html'
find_the_target(start_url, target_words)

#create HTML

head= """
<!DOCTYPE html>
<html>
<head>
<meta http-equiv = "Content-Type" content = "text/html; charset = utf-8" />
</head>
"""

stateCount = """
<p>%s : %d</p>
<p>%s : %d</p>
<p>%s : %d</p>
<p>--------------------------<p>
"""
with open ("ptt_web_scraping.html", "w+" , encoding = 'utf-8', errors = 'replace') as file:
    file.write(head)
    file.write("<body>")
    file.write(stateCount % ("好雷", good, "普雷", ok, "負雷", bad))
    for i in target_title:
        file.write(str(i))
        file.write("<br>")
    file.write("</body></html>")
