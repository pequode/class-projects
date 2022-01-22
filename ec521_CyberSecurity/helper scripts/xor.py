plaintext = "BOSTONUNIVERSITYSUPERSECRETTEXT"

key = "EC521"

ciphertext = ""


#Encryption: xor each letter of the plaintext with the corresponding ciphertext letter
for pos in range(len(plaintext)):
	ciphertext += chr(ord(plaintext[pos])^ord(key[pos%len(key)]))

print(ciphertext)


def Decrpty(EncrptedText,Key):
	DecrptyedText = []
	#Decryption: do the same as encryption
	for pos in range(len(EncrptedText)):
		DecrptyedText.append(ord(EncrptedText[pos])^ord(Key[pos%len(Key)]))
	print(DecrptyedText[:4])
	return DecrptyedText
def PlainTextAttack(KnownText,EncrptedText):
	PartailKey = []
	for pos in range(len(EncrptedText)):
		PartailKey(ord(EncrptedText[pos])^ord(KnownText[pos%len(KnownText)]))
	print(PartailKey)
	return PartailKey

#Plaintext attack: by knowing part of the plaintext, we can recover the key
pt = "BOSTONUNIVERSITY"

recoveredkey = ""



print(recoveredkey)
