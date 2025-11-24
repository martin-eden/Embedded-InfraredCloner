-- Convert signals output to list of integers

--[[
  Author: Martin Eden
  Last mod.: 2025-11-24
]]

--[[
  When tinkering with code of signal recorder I need to visualize

    00047
    Y 00000 00000 00001 00271
    N 00000 00000 00000 00420
    ...

  with something better than my imagination. So I convert it in
  Sublime to

    01271
    00420

  and paste it to Libre Office Calc.

  This script does this conversion job.
]]

local InputFileName = 'Input.txt'
local OutputFileName = 'Output.txt'

do
  local Input = io.open(InputFileName, 'r')
  local NumRecords
  do
    NumRecords = Input:read('n', 'l')

    assert(NumRecords)
  end

  local GetRecord =
    function()
      local IsOnStr, KiloS, S, MilliS, MicroS =
        Input:read(1, 'n', 'n', 'n', 'n', 'l')

      local IsOn

      if (IsOnStr == 'Y') then
        IsOn = true
      elseif (IsOnStr == 'N') then
        IsOn = false
      else
        error('Failed to parse boolean flag value.')
      end

      local TotalNumMicros = 0

      TotalNumMicros = TotalNumMicros + MicroS * 1e0
      TotalNumMicros = TotalNumMicros + MilliS * 1e3
      TotalNumMicros = TotalNumMicros + S * 1e6
      TotalNumMicros = TotalNumMicros + KiloS * 1e9

      return IsOn, TotalNumMicros
    end

  local Output = io.open(OutputFileName, 'w')
  local WriteRecord =
    function(IsOn, NumMicros)
      Output:write(string.format('%05d', NumMicros), '\n')
    end

  for _ = 1, NumRecords do
    local IsOn, NumMicros = GetRecord()
    WriteRecord(IsOn, NumMicros)
  end

  Output:close()
  Input:close()

  print('Done')
end

--[[
  2025-11-24
]]
