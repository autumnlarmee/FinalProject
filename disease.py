import csv
with open('patientdata.csv'
          csv_reader = csv.reader(file)
          for row in csv_reader:
            print(row)
