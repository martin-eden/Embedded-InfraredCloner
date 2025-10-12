// Console interface to record and replay infrared signals

/*
  Author: Martin Eden
  Last mod.: 2025-10-12
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
me_DigitalSignalRecorder::TSignalEvent Signals[NumSignals_Max];

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
  const TUint_4 EmitFreq_Hz = 40000;

  if (!me_ModulatedSignalPlayer::SetFrequency_Hz(EmitFreq_Hz))
    Console.Print("Failed to set frequency.");
}

void PlaySignal(
  TBool IsOn,
  me_Duration::TDuration Duration
)
{
  /*
    No duration adjustments here: Emit() is tuned and Delay() tuning
    is observable only when interleaving with Emit(). And there is
    no interleaving in this function.
  */
  if (IsOn)
    me_ModulatedSignalPlayer::Emit(Duration);
  else
    me_Delays::Delay_Duration(Duration);
}

void ReplayDurations()
{
  const me_Duration::TDuration DelayCompensation = { 0, 0, 0, 190 };
  TUint_2 Index;
  me_DigitalSignalRecorder::TSignalEvent PrevEvent, CurEvent;
  me_Duration::TDuration Duration;
  TBool IsOn;

  if (!DigitalSignalRecorder.GetEvent(&PrevEvent, 1))
    return;

  Index = 2;

  while (true)
  {
    if (!DigitalSignalRecorder.GetEvent(&CurEvent, Index))
      break;

    Duration = CurEvent.Timestamp;
    if (!me_Duration::Subtract(&Duration, PrevEvent.Timestamp))
      break;

    IsOn = !PrevEvent.IsOn;

    if (!IsOn)
    {
      if (!me_Duration::Subtract(&Duration, DelayCompensation))
        Duration = me_Duration::Zero;
    }

    PlaySignal(IsOn, Duration);

    PrevEvent = CurEvent;

    Index = Index + 1;
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
*/
