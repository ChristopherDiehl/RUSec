import re


def get_org_pk(line):
   fsql = open('untitled.sql','r')
   org_lookup_string = line.split(',')[4]

   for sql_line in fsql:
      if org_lookup_string in sql_line:
         pk = sql_line.split("'")[1]
         pk = '"'+pk+'",'
         return pk

###########################################        

fr = open('data1.txt','r')
fw = open('sqlScript.txt','w')


fw.write("delete from sd_grant_general_information where pk like 'm%';\n")
fw.write("delete from eg_document where pk like 'm%';\n")
pk_const ='m2000gd'
gpk_const ='m2000gg'
documenttypepk = '"1001"'
program_area_pk_const = '"1392152523362"'
fo_const = '"1424902020859"'
eg_document_column_values = [2,9]
column_skip_values = [3,4,11,12,13,22,27,32,33,34]
for i, line in enumerate(fr):
   tmp = i+1055 
   tmp = str(tmp)
   eg_document_script = "insert into eg_document(pk,id,documenttypepk,programareapk,title,status)\nvalues( "
   eg_document_script += '"'+pk_const+tmp+'",'
   eg_document_script += '"'+tmp+'",'
   eg_document_script += documenttypepk+','
   eg_document_script += program_area_pk_const+','
   sd_grant_script = """insert into sd_grant_general_information
   (documentpk,pk,opportunityPk,organizationpk,ProjectID,contractNumber,scopeOfWork,projectsummary,masterProject,theme,businessItem,address,city,projectCounty,councilDistrict,legislativeDistrict,projectCommittment,posc,projectEnd,contractLegal,contractSent,contractReceived,contractExecuted,FederalFY,StateFY,awardYear,poNumber)
   values("""
   sd_grant_script += '"'+pk_const+tmp+'",'
   sd_grant_script += '"'+gpk_const+tmp+'",'
   sd_grant_script += fo_const+','

   org_pk = get_org_pk(line)
   if org_pk is not None:
      sd_grant_script += org_pk
   else:
      sd_grant_script += 'NULL,'

   line = line.replace('"','')
   #get data cell values
   for k, data_cell in enumerate(line.split(',')):
       if k in column_skip_values:
           continue

       if k in eg_document_column_values :
           eg_document_script += '"'+data_cell+'",'
       else:
           data_cell = data_cell.replace('\n','')
           sd_grant_script += '"'+data_cell +'",'

   #slice last , off
   sd_grant_script = sd_grant_script [:-1] +');\n'
   eg_document_script = eg_document_script [:-1] + ');\n'

   fw.write(eg_document_script)
   fw.write(sd_grant_script)

