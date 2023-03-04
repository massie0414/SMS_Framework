for %%a in (*.csv) do (
  CsvToSMSBinaryNoCompression.exe %%a
)

move *.bin ../data

