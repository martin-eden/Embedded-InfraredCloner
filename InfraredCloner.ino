// Console interface to record and replay infrared signals

/*
  Author: Martin Eden
  Last mod.: 2025-10-31
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
#include <me_Duration.h>
#include <me_Delays.h>
#include <me_StreamsCollection.h>

#include <me_Menu.h>
#include <me_Console.h>

using
  me_DigitalSignalRecorder::DigitalSignalRecorder;

const TUint_2 NumSignals_Max = 80;
me_DigitalSignalRecorder::TSignal Signals[NumSignals_Max];

void PrintDurations()
{
  me_DigitalSignalRecorder::TextEncoder::
    Save(&DigitalSignalRecorder, Console.GetOutputStream());
}

void ClearDurations()
{
  DigitalSignalRecorder.Clear();
}

void SetupRecorder()
{
  TAddressSegment SignalsSpan = { (TAddress) &Signals, sizeof(Signals) };

  DigitalSignalRecorder.Init(SignalsSpan);
}

void SetupFreqGen()
{
  // 22- 26+ .. 48+ 52-
  const TUint_4 EmitFreq_Hz = 38000;

  if (!me_ModulatedSignalPlayer::SetFrequency_Hz(EmitFreq_Hz))
    Console.Print("Failed to set frequency.");
}

/*
  Replay stored signal
*/
void ReplayDurations()
{
  /*
    Implementation tries to make real observed signal last close to
    original. For that we need to account time for decision-making
    overhead.

    Emit() has built-in compensation. Here we compensate delay time
    for LOW signal.
  */

  const me_Duration::TDuration DelayCompensation = { 0, 0, 0, 390 };

  TUint_2 Index;
  TUint_2 NumSignals;
  me_DigitalSignalRecorder::TSignal Signal;

  NumSignals = DigitalSignalRecorder.GetNumSignals();
  for (Index = 1; Index <= NumSignals; ++Index)
  {
    DigitalSignalRecorder.GetSignal(&Signal, Index);

    if (Signal.IsOn)
      me_ModulatedSignalPlayer::Emit(Signal.Duration);
    else
    {
      if (!me_Duration::Subtract(&Signal.Duration, DelayCompensation))
        Signal.Duration = me_Duration::Zero;

      me_Delays::Delay_PreciseDuration(Signal.Duration);
    }
  }
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
  me_DigitalSignalRecorder::BinaryCodec::Load(&Eeprom, &DigitalSignalRecorder);
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

void PrintDurations_Handler(
  TUint_2 Data [[gnu::unused]],
  TUint_2 Instance [[gnu::unused]]
)
{
  PrintDurations();
}

void Replay_Handler(
  TUint_2 Data [[gnu::unused]],
  TUint_2 Instance [[gnu::unused]]
)
{
  ReplayDurations();
}

void Save_Handler(
  TUint_2 Data [[gnu::unused]],
  TUint_2 Instance [[gnu::unused]]
)
{
  SaveToEeprom();
}

void Load_Handler(
  TUint_2 Data [[gnu::unused]],
  TUint_2 Instance [[gnu::unused]]
)
{
  LoadFromEeprom();
}

// )

void AddMenuItems(
  me_Menu::TMenu * Menu
)
{
  using
    me_Menu::Freetown::ToItem;

  TUint_2 Unused = 0;

  Menu->AddItem(
    ToItem("b", "Begin recording", StartRecording_Handler, Unused)
  );
  Menu->AddItem(
    ToItem("e", "End recording", StopRecording_Handler, Unused)
  );
  Menu->AddItem(
    ToItem("p", "Print data", PrintDurations_Handler, Unused)
  );
  Menu->AddItem(
    ToItem("r", "Replay data", Replay_Handler, Unused)
  );
  Menu->AddItem(
    ToItem("s", "Save data", Save_Handler, Unused)
  );
  Menu->AddItem(
    ToItem("l", "Load data", Load_Handler, Unused)
  );
}

void setup()
{
  Console.Init();

  me_Delays::Init();
  me_ModulatedSignalPlayer::Init();

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
  2025 # # # # # # # # # # #
  2025-10-12
  2025-10-14
  2025-10-31
*/
