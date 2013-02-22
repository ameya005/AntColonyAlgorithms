from numpy import *
import matplotlib.pyplot as plt


def cityReadSACO():
	x,y=loadtxt('city_data.txt', unpack = True)
	order=loadtxt('Data.txt')
	print order
	print x
	print y
	'''order1[]
	x1[]
	y1[]'''
	x1=[]
	y1=[]
	for i in order:
		x1.append(x[i])
		y1.append(y[i])
	x1.append(x[order[0]])
	y1.append(y[order[0]])	
	plt.plot(x1,y1, marker='x', linestyle = '--', color = 'r')
	for i in range(len(order)):
		plt.text(x1[i],y1[i],order[i])
	plt.show() 

def cityReadElitist():
	x,y=loadtxt('city_data_elitist.txt', unpack = True)
	order=loadtxt('Data_elitist.txt')
	print order
	print x
	print y
	'''order1[]
	x1[]
	y1[]'''
	x1=[]
	y1=[]
	for i in order:
		x1.append(x[i])
		y1.append(y[i])
	x1.append(x[order[0]])
	y1.append(y[order[0]])	
	plt.plot(x1,y1, marker='x', linestyle = '--', color = 'r')
	for i in range(len(order)):
		plt.text(x1[i],y1[i],order[i])
	plt.show() 

def cityReadRank():
	x,y=loadtxt('city_data_rank.txt', unpack = True)
	order=loadtxt('Data_rank.txt')
	print order
	print x
	print y
	'''order1[]
	x1[]
	y1[]'''
	x1=[]
	y1=[]
	for i in order:
		x1.append(x[i])
		y1.append(y[i])
	x1.append(x[order[0]])
	y1.append(y[order[0]])	
	plt.plot(x1,y1, marker='x', linestyle = '--', color = 'r')
	for i in range(len(order)):
		plt.text(x1[i],y1[i],order[i])
	plt.show() 
	 
def main():
    city_read()
    city_read_elitist()
    city_read_rank()	


if __name__=="__main__":
	main()
