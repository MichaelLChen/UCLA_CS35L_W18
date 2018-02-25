# ZihengXu 704756821
# Lab 3
# comm.py

#!/usr/bin/python

import sys, locale, string
import argparse

class comm:
	def __init__(self,m_file1, m_file2, alpha, beta, gamma, delta):
		try:
			if m_file1 == '-' and m_file2 == '-':
				print("unable to read two files with stdin")
				exit()
			elif m_file2 == '-':
				f2 = sys.stdin
				f1 = open(m_file1, 'r')
			elif m_file1 == '-':
				f1 = sys.stdin
				f2 = open(m_file2, 'r')
			else:
				f1 = open(m_file1, 'r')
				f2 = open(m_file2, 'r')
			self.lines1 = f1.read().split('\n')
			del self.lines1[len(self.lines1)-1]
			self.lines2 = f2.read().split('\n')
			del self.lines2[len(self.lines2)-1]
			f1.close()
			f2.close()

			self.alpha = alpha
			self.beta = beta
			self.gamma = gamma
			self.delta = delta

		except Exception as e:
			raise e

	def setup(self):
		#print(self.lines1)
		self.setup_newlines(self.lines1)
		#print(self.lines1)
		#print(self.lines2)
		self.setup_newlines(self.lines2)
		#print(self.lines2)

		#print(list(self.lines2))

	def setup_newlines(self, lines):
		for x in range(0,len(lines)):
			if lines[x] == '':
				lines[x] = '\n'
			if lines[x].count(' ') >= 1 and lines[x].isspace():
				lines[x] = '\n' * lines[x].count(' ')

	def unsorted_comparison(self):
		self.setup()
		for m_line1 in self.lines1:
			is_found = False

			for m_line2 in self.lines2:
				if m_line1 == m_line2:
					self.lines2.remove(m_line2)
					self.print_with(m_line1, 3)
					is_found = True
					break
			if is_found == False:
				self.print_with(m_line1, 1)

		for m_line2 in self.lines2:
			self.print_with(m_line2, 2)
		#print(self.lines2)
		#print("unsorted_comp")
		return 0
	def sorted_comparison(self):
		self.setup()
		length1 = len(self.lines1)
		length2 = len(self.lines2)
		i = 0
		j = 0

		while i < length1 and j < length2:
			if self.lines1[i] == self.lines2[j]:
				#sys.stdout.write("\t\t%s\n" %self.lines1[i])
				self.print_with(self.lines1[i], 3)
				i += 1
				j += 1
			elif self.lines1[i] < self.lines2[j]:
				#sys.stdout.write("%s\n" %self.lines1[i])
				self.print_with(self.lines1[i], 1)
				i += 1
			else:
				#sys.stdout.write("\t%s\n" %self.lines2[j])
				self.print_with(self.lines2[j], 2)
				j += 1
		while j < length2:
			self.print_with(self.lines2[j], 2)
			j += 1
		while i < length1:
			self.print_with(self.lines1[i], 1)
			i += 1
		#print("sorted_comp")
		return 0

	def print_with(self, line, state):
		temp_str = ""
		if state == 1:
			if self.alpha == True:
				return 
		elif state == 2:
			if self.beta == True:
				return
			if self.alpha == False:
				temp_str += "\t"
		elif state == 3:
			if self.gamma == True:
				return
			if self.alpha == False:
				temp_str += "\t"
			if self.beta == False:
				temp_str += "\t"
		else:
			pass
		temp_str += line
		sys.stdout.write("%s\n" %temp_str)
	#def printer(self, arg1, arg2, arg3):
		#print("printprint")
		#return 0


def main():
	#locale.setlocale(locale.LC_ALL, 'C')
	usage_msg = """comm.py [OPTION]... FILE1 FILE2

	Output the result after comparing FILE1 and FILE2 line by line."""

	parser = argparse.ArgumentParser(
usage=usage_msg)
	parser.add_argument("-1",
action="store_true", dest="alpha", default=False,
	help="output comparison (default 0)")
	parser.add_argument("-2",
action="store_true", dest="beta", default=False,
	help="output comparison (default 0)")
	parser.add_argument("-3",
action="store_true", dest="gamma", default=False,
	help="output comparison (default 0)")
	parser.add_argument("-u",
action="store_true", dest="delta", default=False,
	help="output comparison (default 0)")
	parser.add_argument("file1", help="file1 argument")
	parser.add_argument("file2", help="file2 argument")
	args = parser.parse_args(sys.argv[1:])

	try:
		alpha = bool(args.alpha)
		beta = bool(args.beta)
		gamma = bool(args.gamma)
		delta = bool(args.delta)
	except:
		parser.error("invalid option type: {0}".
					format(args.alpha))
	
	input_file_1 = args.file1
	input_file_2 = args.file2

	try:
		m_comm = comm(
			input_file_1, input_file_2, 
			alpha, beta, gamma, delta)
		if delta:
			m_comm.unsorted_comparison()
		else:
			m_comm.sorted_comparison()
		#m_comm.printer(alpha, beta, gamma)
	except IOError as e:
		errno = e.errno
		strerror = e.strerror
		parser.error("I/O error({0}): {1}".
					  format(errno, strerror))

if __name__ == "__main__":
	main()


