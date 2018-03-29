import json
import sqlite3
file = open("some.txt",'r')

res_arr = []
for line in file:
    str = line
    arr = [i for i in str]
    str = ''.join(arr[1:len(arr) - 2])
    for i in str.split("} {"):
        subi = i.split("\'")[1::2][1::2]
        count = 0
        dop_arr = []

        for j in subi:
            count = count + 1
            dop_arr.append(j)
            if count == 5:
                if len(dop_arr[3])>2 and len(dop_arr[1])>2:
                    res_arr.append(dop_arr.copy())
                dop_arr.clear()
                count = 0

dict = {}
for i in res_arr:
    dict.update({i[0]:''})

rootAnagrams = []

for d in dict:
    rootAnagrams.append((d,))

db = sqlite3.connect("sample1.db")
cursor = db.cursor()

rows = []

for i in res_arr:
    cursor.execute("SELECT id,root FROM rootAnagrams WHERE root = ?",(i[0],))
    rows.append((i[1],i[2],i[3],i[4],cursor.fetchone()[0]))


cursor.executemany("""INSERT INTO leefAnagrams(word1,value1,word2,value2,id_root) VALUES (?,?,?,?,?)""", rows)
db.commit()