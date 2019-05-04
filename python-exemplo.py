import threading
import time
import random

PENSANDO = 0
FAMINTO = 1
COMENDO = 2
NUMFIL = 5

mutex = threading.Semaphore(1)
s = [threading.Semaphore(1) for i in range(NUMFIL)]

estado = [None] * NUMFIL

def esquerda(i):
    return (i+NUMFIL-1)%NUMFIL

def direita(i):
    return(i+1)%NUMFIL

def pensar(i):
    print("Filósofo " + str(i) + " está pensando...")
    time.sleep(random.randint(0, 5))

def comer(i):
    print("Filósofo " + str(i) + " está comendo...")
    time.sleep(random.randint(0, 5))

def tentar(i):
    if estado[i] == FAMINTO and estado[esquerda(i)] != COMENDO and estado[direita(i)] != COMENDO:
        estado[i] = COMENDO
        s[i].release()

def pegarGarfos(i):
    mutex.acquire()
    estado[i] = FAMINTO
    tentar(i)
    mutex.release()
    s[i].acquire()

def liberarGarfos(i):
    mutex.acquire()
    estado[i] = PENSANDO
    tentar(esquerda(i))
    tentar(direita(i))
    mutex.release()

def filosofo(i):
    while(True):
        pensar(i)
        pegarGarfos(i)
        comer(i)
        liberarGarfos(i)

fil1 = threading.Thread(target=filosofo, args=(0,))
fil2 = threading.Thread(target=filosofo, args=(1,))
fil3 = threading.Thread(target=filosofo, args=(2,))
fil4 = threading.Thread(target=filosofo, args=(3,))
fil5 = threading.Thread(target=filosofo, args=(4,))

fil1.start()
fil2.start()
fil3.start()
fil4.start()
fil5.start()

fil1.join()
fil2.join()
fil3.join()
fil4.join()
fil5.join()

