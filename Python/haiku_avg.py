import sys
from urllib.request import urlopen
from bs4 import BeautifulSoup
from html.parser import HTMLParser

DEGUG=True

class HaikuParser(HTMLParser):
    def handle_starttag(self, tag, attrs):
        print(tag)

    def handle_endtag(self, tag):
        print(tag)

    def handle_data(self, data):
        pass

data = urlopen(sys.argv[1])
soup = BeautifulSoup(data.read(), 'html.parser')
contents = soup.prettify()

if DEGUG:
    f = open('haiku_avg_out_tmp.txt', 'w')
    f.write(contents)
    f.close()

parser = HaikuParser()
parser.feed(contents)
