import serial

def leitura():
    conn = serial.Serial('COM1', 9600, timeout = 100)
    resp = []
    a = conn.readline()
    resp.append(a)

    i = 0
    for l in resp:
        i += 1
        return(l)

def main():
    c = 0
    while(c<100):
        print(leitura())
        c+=1
while(True):
    main()
    resposta = input("Deseja sair? ")
    if resposta == "sim":
        exit()
