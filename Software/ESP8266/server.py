try:
	import usocket as socket
except:
	import socket

try:
	import uos as os
except:
	import os

try:
	import ujson as json
except:
	import json

import machine

led = machine.Pin(2,machine.Pin.OUT)
pwmLed = machine.PWM(led)
pwmLed.freq(1)
pwmLed.duty(512)

def process_rq(_method, _content):
	if _method == "GET":
		if _content == "/":
			return "index.html"
		else:
			file = _content[1:]
			try:
				os.stat(file)
				return file
			except:
				return False 
	if _method == "POST":
		_content_arr = _content.split('/')
		if _content_arr[1] == "SaveToSD":
			return "success.txt"
		try:
			print("\'{\""+_content_arr[1]+"\": "+_content_arr[2]+"}\'")
			with open("param.json", "r") as f:
				json_obj = json.loads(f.read())
				json_obj[_content_arr[1]] = float(_content_arr[2])
			with open("param.json", "w") as f:
				string = json.dumps(json_obj)
				f.write(string)
			return "success.txt"
		except:
			return "error.txt"
	return False


CONTENT = b"""\
HTTP/1.0 200 OK
Hello #%d from MicroPython!
"""

def main():
	s = socket.socket()
	# Binding to all interfaces - server will be accessible to other hosts!
	ai = socket.getaddrinfo("0.0.0.0", 80)
	print("Bind address info:", ai)
	addr = ai[0][-1]

	s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
	s.bind(addr)
	s.listen(5)
	print("Listening, connect your browser to http://<this_host>:8080/")

	counter = 0
	while True:
		res = s.accept()
		pwmLed.freq(10)
		client_sock = res[0]
		client_addr = res[1]
		print("Client address:", client_addr)
		print("Client socket:", client_sock)


		client_stream = client_sock

		rq = client_stream.readline().decode().split('\r\n')[0]
		rq_arr = rq.split(" ")
		method = rq_arr[0]
		content = rq_arr[1]
		print("rq_method : " + method)
		print("rq_content: " + content)

		file = process_rq(method, content)
		if not file:
			f = open("404Header.http", 'r')
			client_stream.sendall(f.read())
		else:
			f = open("200Header.http", 'r')
			header = f.read() % (os.stat(file)[6])
			client_stream.sendall(header)
			with open(file, 'r') as f:
				while True:
					txt = f.read(10)
					if txt == '':
						break
					else:
						client_stream.sendall(txt)
					
		while True:
			h = client_stream.readline()
			if h == b"" or h == b"\r\n":
				break
		client_stream.write(CONTENT % counter)
		client_stream.close()
		print()
		pwmLed.freq(1)

main()