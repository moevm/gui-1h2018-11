dict1 = {
    'о': 55414481,
    'e': 42691213,
    'а': 40487008,
    'и': 37153142,
    'у': 13245712,
    'я': 10139085,
    'ы': 9595941,
    'ю': 3220715,
    'э': 1610107,
    'ё': 184928,
}

dict2 = {
    'н': 33838881,
    'т': 31620970,
    'с': 27627040,
    'р': 23916825,
    'в': 22930719,
    'л': 22230174,
    'к': 17653469,
    'м': 16203060,
    'д': 15052118,
    'п': 14201572,
    'г': 8564640,
    'ь': 8784613,
    'з': 8329904,
    'б': 8051767,
    'ч': 8051767,
    'й': 6106262,
    'х': 4904176,
    'ж': 4746916,
    'ш': 3678738,
    'ц': 2438807,
    'щ': 1822476,
    'ф': 1335747,
    'ъ': 185452
}

col_v = 0
col_c = 0

dict1_2 = {}
dict2_2 = {}

for key in dict1.values():
    col_v = col_v + key
for key in dict2.values():
    col_c = col_c + key

for k, val in dict1.items():
    dict1_2.update({k: round((val / col_v) * 1000)})

for k, val in dict2.items():
    dict2_2.update({k: round((val / col_c) * 1000)})

dict2_2.update({'н': 115})

col_v = 0
col_c = 0

for k, val in dict1_2.items():
    dict1_2.update({k: val+col_v})
    col_v = col_v + val


for k, val in dict2_2.items():
    dict2_2.update({k: val+col_c})
    col_c = col_c + val

for val in dict2_2.keys():
    print(val,end="")

print("нтсрвлкмдпгьзбчйхжшцщфъ".upper())
# for k, val in dict1_2.items():
#     print(k .__str__()+ ": " + val.__str__())

