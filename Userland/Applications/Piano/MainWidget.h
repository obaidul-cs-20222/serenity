/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 * Copyright (c) 2019-2020, William McPherson <willmcpherson2@gmail.com>
 * Copyright (c) 2021, JJ Roberts-White <computerfido@gmail.com>
 * Copyright (c) 2022, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "Music.h"
#include <LibDSP/Keyboard.h>
#include <LibGUI/Widget.h>

class AudioPlayerLoop;
class TrackManager;
class WaveWidget;
class RollWidget;
class SamplerWidget;
class KeysWidget;
class KnobsWidget;
class PlayerWidget;

class MainWidget final : public GUI::Widget {
    C_OBJECT_ABSTRACT(MainWidget)
public:
    static ErrorOr<NonnullRefPtr<MainWidget>> try_create(TrackManager&, AudioPlayerLoop&);
    virtual ~MainWidget() override = default;

    ErrorOr<void> add_track_actions(GUI::Menu&);

    void set_octave_and_ensure_note_change(DSP::Keyboard::Direction);
    void set_octave_and_ensure_note_change(int);

private:
    explicit MainWidget(TrackManager&, AudioPlayerLoop&);

    ErrorOr<void> initialize();

    virtual void keydown_event(GUI::KeyEvent&) override;
    virtual void keyup_event(GUI::KeyEvent&) override;
    virtual void custom_event(Core::CustomEvent&) override;

    bool note_key_action(int key_code, DSP::Keyboard::Switch);
    bool special_key_action(int key_code);

    void turn_off_pressed_keys();
    void turn_on_pressed_keys();

    TrackManager& m_track_manager;
    AudioPlayerLoop& m_audio_loop;

    RefPtr<WaveWidget> m_wave_widget;
    RefPtr<RollWidget> m_roll_widget;
    RefPtr<SamplerWidget> m_sampler_widget;
    RefPtr<GUI::TabWidget> m_tab_widget;
    RefPtr<GUI::Widget> m_keys_and_knobs_container;
    RefPtr<KeysWidget> m_keys_widget;
    RefPtr<KnobsWidget> m_knobs_widget;
    RefPtr<PlayerWidget> m_player_widget;

    // Not the piano keys, but the computer keyboard keys!
    bool m_keys_pressed[key_code_count] { false };
};
