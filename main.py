import os
import docplex.cp.utils_visu as visu
import matplotlib.pyplot as plt
from pylab import rcParams
from docplex.cp.model import *


os.system('/home/wiktoria/Dokumenty/python/kod/main')


dane = []
with open('/home/wiktoria/Dokumenty/python/kod/dane.txt', 'r') as f:
    lines = [line.rstrip() for line in f]
    lines=[l.split(' ') for l in lines]
    for i in range(len(lines)):
        for j in range(len(lines[i])):
            lines[i][j]=int(lines[i][j])
        dane.append(lines[i])

f.close()
#-------------------------- faktyczny program do robienia wykresow ------------------------

machines = [*range(1, dane[0][1]+1)]
process = []
for i in range(dane[0][0]):
    process.append(dane[i+1][1])
mdl = CpoModel()

for k in range(3):
    intervals = []
    t =[]
    for i in machines:
        line =[]
        line.append(i)
        for j in range(len(dane[-3+k])):
            if dane[-3+k][j]==i:
                line.append(j+1)

        size = len(line)-1
        line.insert(1,size)
        t.append(line)

    for i in range(dane[0][1]): #maszyny
        maszyna=0
        for j in range(2,len(t[i])): #procesy
            if t[i][1]==1: #
                costam = []
                costam.append(t[i][j])
                costam.append(0)
                costam.append(process[t[i][j]-1])
                intervals.append(costam)
                break
            elif t[i][1]==2:
                index1=t[i][j]-1
                index2 = t[i][j+1] - 1
                costam1 = []
                costam2 = []
                costam1.append(t[i][j])
                costam1.append(0)
                costam1.append(process[index1])
                costam2.append(t[i][j+1])
                costam2.append(process[index1])
                costam2.append(process[index2])
                intervals.append(costam1)
                intervals.append(costam2)
                break
            elif t[i][1]>2:
                if j<len(t[i])-1:
                    index1 = t[i][j] - 1
                    index2 = t[i][j + 1] - 1
                    costam1 = []
                    costam2 = []
                    if(maszyna == 0):
                        costam1.append(t[i][j])
                        costam1.append(maszyna)
                        maszyna += process[index1]
                        costam1.append(maszyna)
                        costam2.append(t[i][j+1])
                        costam2.append(maszyna)
                        maszyna += process[index2]
                        costam2.append(maszyna)
                        intervals.append(costam1)
                        intervals.append(costam2)
                    else:
                        costam2.append(t[i][j+1])
                        costam2.append(maszyna)
                        maszyna += process[index2]
                        costam2.append(maszyna)
                        intervals.append(costam2)
                else:
                    break
    #------------------rysowanie--------------------
    import matplotlib.pyplot as plt
    fig,gnt = plt.subplots()
    gnt.set_ylim(0,50)
    gnt.set_xlim(0,200)

    gnt.set_xlabel('Time')
    gnt.set_ylabel('Machines')

    y_odleglosc = [15]
    for i in range(1,len(machines)):
        y_odleglosc.append(y_odleglosc[0]+10*i)

    gnt.set_yticks(y_odleglosc)
    maszyny_wykres = []
    for m in machines:
        maszyny_wykres.append('M'+str(m))
    gnt.set_yticklabels(maszyny_wykres)
    gnt.grid(True)
    color=['tab:pink','tab:red','tab:orange','tab:green','tab:brown','tab:grey','tab:cyan','tab:blue','tab:purple']
    legenda=[]
    counter =0
    for i in range(len(t)):
        for j in range(counter,counter+t[i][1]):
            gnt.broken_barh([(intervals[j][1],intervals[j][2])],(10+10*i,9),facecolors=(color[j]))
            legenda.append('P'+str(intervals[j][0]))
        counter+=t[i][1]
    plt.legend(legenda)
    if(k==0):
        plt.title('Brute Force')
        plt.savefig("/home/wiktoria/Dokumenty/python/kod/wykresy/bruteforce.png")
    if (k == 1):
        plt.title('Genetic Algorithm')
        plt.savefig("/home/wiktoria/Dokumenty/python/kod/wykresy/genetic.png")
    if (k == 2):
        plt.title('Greedy')
        plt.savefig("/home/wiktoria/Dokumenty/python/kod/wykresy/greedy.png")
#plt.show()





    #for i in range(dane[0][1]):
        #visu.sequence(name='M' + str(t[i][0]))
        #for j in range(2,len(t[i])):
            #print(intervals[t[i][j]-1][0])
            #print(intervals[t[i][j]-1][1])
            #if k == 0: visu.interval(intervals[t[i][j]-1][0],intervals[t[i][j]-1][1],'red', 'P' + str(t[i][j]))
            #elif k == 1: visu.interval('orange', 'P' + str(t[i][j]))
            #elif k == 2: visu.interval('yellow', 'P' + str(t[i][j]))

    #visu.show()
    #if k == 0:
        #with Show('/home/wiktoria/Dokumenty/python/kod/wykresy/bruteforce.png'):
           # visu.show()
    #elif k == 1:
       # with Show('/home/wiktoria/Dokumenty/python/kod/wykresy/genetic.png'):
           # visu.show()

    #elif k == 2:
     #   with Show('/home/wiktoria/Dokumenty/python/kod/wykresy/greedy.png'):
        #    visu.show()


