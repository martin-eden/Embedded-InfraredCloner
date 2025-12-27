// Console interface to record and replay infrared signals

/*
  Author: Martin Eden
  Last mod.: 2025-12-27
*/

/*
  That's like the 3rd of 4th incarnation of this idea

  Caveat of emitting IR signals that digitalWrite(HIGH) won't work.
  Receiver will see just one strobe. To keep signal running
  you need to flip it quite fast, near 38 kHz.

  So it can capture digital signal. It can replay digital signal
  using base frequency.

  Console interface allows you to remotely control this from
  another program.
*/

/*
  Wiring

    8 Input
    6 Output
*/

#include <me_BaseTypes.h>

#include <me_DigitalSignalRecorder.h>
#include <me_ModulatedSignalPlayer.h>
#include <me_Delays.h>
#include <me_StreamsCollection.h>

#include <me_Menu.h>
#include <me_Console.h>

using
  me_DigitalSignalRecorder::DigitalSignalRecorder;

static const TUint_2 NumSignals_Max = 75;
static me_DigitalSignalRecorder::TSignal Signals[NumSignals_Max];

void ClearDurations()
{
  DigitalSignalRecorder.Clear();
}

/*
  Play stored signal
*/
void PlayDurations()
{
  /*
    Implementation tries to make real observed signal last close to
    original. For that we need to account time for decision-making
    and data fetching.

    Emit() has built-in compensation. Here we compensate delay time
    for LOW signal. It consists of loop overhead and overhead in
    calling and returning from Delay_Us().
  */

  const TUint_4 DelayCompensation_Us = 910;

  TUint_2 Index;
  TUint_2 NumSignals;
  me_DigitalSignalRecorder::TSignal Signal;

  NumSignals = DigitalSignalRecorder.GetNumSignals();

  for (Index = 1; Index <= NumSignals; ++Index)
  {
    DigitalSignalRecorder.GetSignal(&Signal, Index);

    if (Signal.IsOn)
      me_ModulatedSignalPlayer::Emit_Us(Signal.Duration_Us);
    else
      if (Signal.Duration_Us > DelayCompensation_Us)
        me_Delays::Delay_Us(Signal.Duration_Us - DelayCompensation_Us);
      else
        ;
  }
}

void PrintDurations()
{
  me_DigitalSignalRecorder::TextCodec::
    Save(&DigitalSignalRecorder, Console.GetOutputStream());
}

void ParseDurations()
{
  if (!
    me_DigitalSignalRecorder::TextCodec::
      Load(&DigitalSignalRecorder, Console.GetInputStream())
  )
    Console.Print("Failed to parse");
}

void SaveToEeprom()
{
  me_StreamsCollection::TEepromOutputStream Eeprom;

  Eeprom.Init();
  me_DigitalSignalRecorder::BinaryCodec::Save(&DigitalSignalRecorder, &Eeprom);
}

void LoadFromEeprom()
{
  me_StreamsCollection::TEepromInputStream Eeprom;

  Eeprom.Init();
  me_DigitalSignalRecorder::BinaryCodec::Load(&DigitalSignalRecorder, &Eeprom);
}

// ( Menu item handlers

void StartRecording_Handler(
  TUint_2 Data [[gnu::unused]],
  TUint_2 Instance [[gnu::unused]]
)
{
  ClearDurations();
  me_DigitalSignalRecorder::StartRecording();
}

void StopRecording_Handler(
  TUint_2 Data [[gnu::unused]],
  TUint_2 Instance [[gnu::unused]]
)
{
  me_DigitalSignalRecorder::StopRecording();
}

void Play_Handler(
  TUint_2 Data [[gnu::unused]],
  TUint_2 Instance [[gnu::unused]]
)
{
  PlayDurations();
}

void ExternalSave_Handler(
  TUint_2 Data [[gnu::unused]],
  TUint_2 Instance [[gnu::unused]]
)
{
  PrintDurations();
}

void ExternalLoad_Handler(
  TUint_2 Data [[gnu::unused]],
  TUint_2 Instance [[gnu::unused]]
)
{
  ClearDurations();
  ParseDurations();
}

void InternalSave_Handler(
  TUint_2 Data [[gnu::unused]],
  TUint_2 Instance [[gnu::unused]]
)
{
  SaveToEeprom();
}

void InternalLoad_Handler(
  TUint_2 Data [[gnu::unused]],
  TUint_2 Instance [[gnu::unused]]
)
{
  ClearDurations();
  LoadFromEeprom();
}

// )

void AddMenuItems(
  me_Menu::TMenu * Menu
)
{
  using
    me_Menu::Freetown::ToItem;

  const TUint_2 Unused = 0;

  Menu->AddItem(
    ToItem("b", "Begin recording", StartRecording_Handler, Unused)
  );
  Menu->AddItem(
    ToItem("e", "End recording", StopRecording_Handler, Unused)
  );
  Menu->AddItem(
    ToItem("p", "Play data", Play_Handler, Unused)
  );
  Menu->AddItem(
    ToItem("es", "Print data to outside", ExternalSave_Handler, Unused)
  );
  Menu->AddItem(
    ToItem("el", "Load data from outside", ExternalLoad_Handler, Unused)
  );
  Menu->AddItem(
    ToItem("is", "Save data to internal memory", InternalSave_Handler, Unused)
  );
  Menu->AddItem(
    ToItem("il", "Load data from internal memory", InternalLoad_Handler, Unused)
  );
}

void SetupRecorder()
{
  DigitalSignalRecorder.Init(AsAddrSeg_M(Signals));
  me_DigitalSignalRecorder::PrepareRecorder();
}

void SetupFreqGen()
{
  // 22- 26+ .. 48+ 52-
  const TUint_4 EmitFreq_Hz = 38000;

  me_ModulatedSignalPlayer::Init();

  if (!me_ModulatedSignalPlayer::SetFrequency_Hz(EmitFreq_Hz))
    Console.Print("Failed to set frequency.");
}

void setup()
{
  Console.Init();

  SetupRecorder();

  SetupFreqGen();

  Console.Print("IR signal player/recorder");

  {
    me_Menu::TMenu Menu;

    AddMenuItems(&Menu);

    Menu.AddBuiltinCommands();
    Menu.Print();

    Menu.Run();
  }

  Console.Print("Done");
}

void loop()
{
}

/*
  2025 # # # # # # # # # # # # #
  2025-10-31
  2025-11-10
  2025-11-18
  2025-12-27
*/
