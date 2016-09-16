from datetime import datetime, timedelta
import os.path
import socket

import sys
if int(sys.version[0]) < 3:
    from urllib import urlretrieve
    from urllib2 import URLError # a nasty hack that covers for Python3's URLError
else:
    from urllib.request import urlretrieve
    from urllib.error import URLError

now = datetime.now()

def strToTime(time_s):
    return datetime.strptime(time_s, '%I:%M%p').time()
            
def strToDate(date_s):
    return datetime.strptime(date_s, '%d %B %Y').date()

def strToList(s, f=lambda x:x):
    return [f(x.strip()) for x in s.split(',')]

"""
Dependencies:
    from datetime import datetime
    import os.path
    import socket
    import urllib.error
    import urllib.request
"""
class ScheduleLoader(object):
    def __init__(self, schedule_path, schedule_url):
        schedule_info_cache_name = os.path.join(os.path.dirname(__file__), '.sinfo.cache')
        try:
            urlretrieve(schedule_url, schedule_info_cache_name)
        except (socket.gaierror, URLError, IOError): #IOError for Python2 compatiblity
            pass
        
        with open(schedule_path, 'r') as sfile:
            self.classes = strToList(sfile.readline())
            self.schedule = []
        
            for i in range(6):
                day_schedule = strToList(sfile.readline(), int)
                self.schedule.append(day_schedule)

            sport = sfile.readline().strip()
            if sport.upper() == 'NONE':
                self.sport = None
                self.sport_times = None
            else:
                self.sport = sport
                self.sport_times = strToList(sfile.readline(), strToTime)

        with open(schedule_info_cache_name, 'r') as sinfo_file:
            self.reg_mod_times  = strToList(sinfo_file.readline(), strToTime)
            self.late_mod_times = strToList(sinfo_file.readline(), strToTime)
            self.reg_start_time, self.reg_end_time = strToList(sinfo_file.readline(), strToTime)
            self.late_start_time, self.late_end_time = strToList(sinfo_file.readline(), strToTime)
            rec_cycle_day_date_str, rec_cycle_day_str = strToList(sinfo_file.readline())
            self.rec_cycle_date = strToDate(rec_cycle_day_date_str)
            self.rec_cycle_day = ord(rec_cycle_day_str) - ord('A')
            sinfo_file.readline() # Line can be whatever, typically, 'Holidays:'
            self.holidays = []
            self.weird_days = []
            self.weird_info = []
            
            while (True):
                line = sinfo_file.readline().strip()
                
                if line == 'Weird Days:':
                    break
                
                self.holidays.append(strToDate(line))
            
            while (True):
                line = sinfo_file.readline().strip()
                
                if not line:
                    break
                
                weird_day, weird_note = strToList(line)
                self.weird_days.append(strToDate(weird_day))
                self.weird_info.append(weird_note)

class ScheduleInfo2(ScheduleLoader):
    def __init__(self, schedule_path, schedule_url):
        super().__init__(schedule_path, schedule_url)
        
        self.now = datetime.now()
        self.cycle_day = (self.rec_cycle_day + self.schoolDayCount(self.rec_cycle_day_date, now.date())) % 6
        self.in_school = self.isSchoolDay(now) and self.start_time < now.time() < self.end_time
        
        if self.isSchoolDay(now.date()):
            if self.isSchoolDay(now.date(), False):
                # regular/late schedule
                pass
            else:
                # weird schedule
                pass
        else:
            pass
        
    def schoolDayCount(self, start_date, end_date):
        school_days = 0

        for i in range((end_date - start_date).days):
            day = start_date + timedelta(i + 1)
            if self.isSchoolDay(day, False):
                school_days += 1
            
        return school_days
    
    def isSchoolDay(self, date, include_weird=True):
        haveSchool = date.weekday() < 5 and date not in self.holidays
        return haveSchool and not (date in self.weird_days and not include_weird)

class ScheduleInfo(object):
    def __init__(self, schedule_path):
        f = open(schedule_path, 'r')
        
        self.classes = [x.strip() for x in f.readline().split(',')]
        self.schedule = []
        
        for i in range(6):
            day_schedule = [int(x.strip()) for x in f.readline().split(',')]
            self.schedule.append(day_schedule)

        rec_cycle_day_date, rec_cycle_day = [x.strip() for x in f.readline().split(',')]
        reg_mod_times = [datetime.strptime(x.strip(), '%I:%M%p').time() for x in f.readline().split(',')]
        late_mod_times = [datetime.strptime(x.strip(), '%I:%M%p').time() for x in f.readline().split(',')]
        reg_start_time, reg_end_time = [datetime.strptime(x.strip(), '%I:%M%p').time() for x in f.readline().split(',')]
        late_start_time, late_end_time = [datetime.strptime(x.strip(), '%I:%M%p').time() for x in f.readline().split(',')]
        
        rec_cycle_day_date = datetime.strptime(rec_cycle_day_date, '%d %B %Y').date()
        rec_cycle_day = ord(rec_cycle_day) - ord('A')
        self.cycle_day = rec_cycle_day + self.schoolDayCount(rec_cycle_day_date, now.date()) % 6
        
        self.mod_times = late_mod_times if now.weekday() == 2 or self.cycle_day == 3 else reg_mod_times
        self.start_time = late_start_time if now.weekday() == 2 else reg_start_time
        self.end_time = late_end_time if now.weekday() == 2 else reg_end_time
        
        self.in_school = self.start_time < now.time() < self.end_time and self.isSchoolDay(now)

    """ mod, cycle day (implicit) --> class name """
    def className(self, mod):
        return self.classes[self.schedule[self.cycle_day][mod]]
        
    def modTime(self, mod):
        return self.mod_times[mod]

    def isSchoolDay(self, day):
        return day.weekday() < 5

    """ list of mod times, current time (implicit) --> current mod """
    def currentMod(self, current_time=now.time()):
        for i in reversed(range(len(self.mod_times))):
            if current_time > self.mod_times[i]:
                return i

    """ mod, day, schedule --> class starting mod """
    def classStartMod(self, mod):
        current_class = self.schedule[self.cycle_day][mod]
    
        while mod > 0 and self.schedule[self.cycle_day][mod - 1] == current_class:
            mod -= 1
        
        return mod

    """ mod, day, schedule --> next class starting mod """
    def nextClassMod(self, mod):
        current_class = self.schedule[self.cycle_day][mod]
    
        while mod < len(self.schedule[self.cycle_day]) and self.schedule[self.cycle_day][mod] == current_class:
            mod += 1
        
        return mod
        
    """ early date, later date --> work days between them """
    def schoolDayCount(self, start_date, end_date):
        school_days = 0
    
        for i in range((end_date - start_date).days):
            day = start_date + timedelta(i + 1)
            school_days += self.isSchoolDay(day)
            
        return school_days
        
    def numMods(self):
        return len(self.schedule[0])

    def nextSchoolDay(self):
        i = 1
        while True:
            day = now.date() + timedelta(i)
            
            if self.isSchoolDay(day):
                return day
            
            i += 1

def main():
    schedule_info = ScheduleInfo(os.path.join(os.path.dirname(__file__), 'schedule.txt'))

    if schedule_info.in_school:
        current_mod = schedule_info.currentMod()
        current_class = schedule_info.className(current_mod)
        current_class_start_mod = schedule_info.classStartMod(current_mod)
        current_class_time = schedule_info.modTime(current_class_start_mod).strftime('%I:%M %p')
        print(current_class, 'started at', current_class_time)
        
        next_class_mod = schedule_info.nextClassMod(current_mod)
        if next_class_mod == schedule_info.numMods():
            print('School ends at', schedule_info.end_time)
        else:
            next_class = schedule_info.className(next_class_mod)
            next_class_time = schedule_info.modTime(next_class_mod).strftime('%I:%M %p')
            print(next_class, 'starts at', next_class_time)
    else:
        print('Not ready to use!')
        
        """
        next_school_day = schedule_info.nextSchoolDay()
        tomorrow = now.date() + timedelta(1)
        if next_school_day == tomorrow:
            print('School is tomorrow (' + schedule_day + ' day) at ' + school_time)
        elif next_school_day == today:
            print('School today (' + schedule_day + ' day) starts at ' + school_time)
        else:
            print('School is on' + next_school_day + ' (' + schedule_day + ' day) at ' + school_time)
        """

''' remove later @temp '''
from pprint import pprint

if __name__ == '__main__':
    main()
    sl = ScheduleLoader('schedule2.txt', 'http://jeffaryan.com/schedule_keeper/hh_schedule_info.txt')
    pprint(vars(sl))

"""
Things program needs to be aware of:
    * What days we have school
    * What kind of day those are
    * What the shcedule is for those days
    * The time
    * User's schedule
"""