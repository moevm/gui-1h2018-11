from urllib import request
from urllib import parse
from bs4 import BeautifulSoup
import sqlite3
import time

# select word FROM 'ozhigov' where length(word) = 9

def req(word):
    myUrl = "https://sanstv.ru/anagram/word-" + parse.quote_plus(word) + "/strong-2?"

    answer = request.urlopen(myUrl)

    site = answer.read()

    soup = BeautifulSoup(site)

    ol = soup.find('ol', class_='words')

    if ol is None:
        return []

    pair_of_words = []

    for row in ol.find_all('li'):
        spans = row.find_all('span')
        if len(spans) == 0:
            break
        if len(spans) == 2 and spans[0]['title'] != '' and spans[1]['title'] != '':
            pair_of_words.append({
                'word0': word,
                'word1': spans[0].text,
                'title1': spans[0]['title'],
                'word2': spans[1].text,
                'title2': spans[1]['title']
            })
    return pair_of_words


conn = sqlite3.connect("sample1.db")
# conn.row_factory = sqlite3.Row
cursor = conn.cursor()
sql = "select word FROM 'ozhigov' where length(word) = 9"
cursor.execute(sql)
for row in cursor.fetchall():
    file = open("some.txt", "a")
    res = req(row[0])
    if len(res) != 0:
        file.write(" ".join(str(x) for x in res))  # or use fetchone()
        file.write("\n")
        print(res.__len__())
    file.close()
    time.sleep(2)


