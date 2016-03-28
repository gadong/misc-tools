format 75

classinstance 128028 class_ref 128028 // MediaApp
  name ""   xyz 7.20358 4.5 2000 life_line_z 2000
classinstance 128156 class_ref 128156 // MediaPlayer
  name ""   xyz 84.2407 4.5 2000 life_line_z 2000
classinstance 128284 class_ref 128284 // Client
  name ""   xyz 190.801 4.42586 2000 life_line_z 2000
classinstance 128412 class_ref 128412 // AudioOuptput
  name ""   xyz 277.33 4.4 2000 life_line_z 2000
classinstance 128540 class_ref 128540 // NuPlayerDriver
  name ""   xyz 394.451 4.5 2000 life_line_z 2000
classinstance 128668 class_ref 128668 // NuPlayer
  name ""   xyz 499.938 4.5 2000 life_line_z 2000
classinstance 128796 class_ref 129052 // GenericSource
  name ""   xyz 574.236 4.5 2000 life_line_z 2000
classinstance 128924 class_ref 128796 // NuPlayer::Render
  name ""   xyz 674.886 4.5 2000 life_line_z 2000
classinstance 129052 class_ref 128924 // NuPlayer::Decoder
  name ""   xyz 792.793 5.19438 2000 life_line_z 2000
durationcanvas 129180 classinstance_ref 128028 // :MediaApp
  color mediumgreen
  xyzwh 36 56.3 2010 11 461
end
durationcanvas 129308 classinstance_ref 128156 // :MediaPlayer
  color mediumgreen
  xyzwh 119 57.45 2010 11 25
end
durationcanvas 129564 classinstance_ref 128156 // :MediaPlayer
  color mediumgreen
  xyzwh 119 84.5 2010 11 412
end
durationcanvas 129820 classinstance_ref 128284 // :Client
  color mediumyellow
  xyzwh 209 87.15 2010 11 34
end
durationcanvas 130332 classinstance_ref 128284 // :Client
  color mediumyellow
  xyzwh 209 144.7 2010 11 341
end
durationcanvas 130588 classinstance_ref 128540 // :NuPlayerDriver
  color mediumyellow
  xyzwh 437 154.35 2010 11 28
end
durationcanvas 130844 classinstance_ref 128668 // :NuPlayer
  color mediumyellow
  xyzwh 526 164.9 2010 11 29
end
durationcanvas 131100 classinstance_ref 128412 // :AudioOuptput
  color mediumyellow
  xyzwh 316 193.25 2010 11 25
end
durationcanvas 131868 classinstance_ref 128540 // :NuPlayerDriver
  color mediumyellow
  xyzwh 437 230.65 2010 11 46
end
durationcanvas 132124 classinstance_ref 128540 // :NuPlayerDriver
  color mediumyellow
  xyzwh 437 310.2 2010 11 149
end
durationcanvas 132380 classinstance_ref 128668 // :NuPlayer
  color mediumyellow
  xyzwh 526 318.45 2010 11 144
  overlappingdurationcanvas 133148
    color red
    xyzwh 532 410.5 2020 11 40
  end
end
durationcanvas 132636 classinstance_ref 128796 // :GenericSource
  color mediumyellow
  xyzwh 617 348.15 2010 11 31
end
durationcanvas 132892 classinstance_ref 128796 // :GenericSource
  color mediumyellow
  xyzwh 617 390.4 2010 11 37
end
durationcanvas 133404 classinstance_ref 128668 // :NuPlayer
  color mediumyellow
  xyzwh 526 252.6 2010 11 41
  overlappingdurationcanvas 133660
    color red
    xyzwh 532 263.75 2020 11 25
  end
end
msg 129436 synchronous
  from durationcanvas_ref 129180
  to durationcanvas_ref 129308
  yz 69 2015 explicitmsg "<<create>>"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 52 54
msg 129692 synchronous
  from durationcanvas_ref 129180
  to durationcanvas_ref 129564
  yz 123 2015 explicitmsg "setDataSource()"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 38 109
msg 129948 asynchronous
  from durationcanvas_ref 129564
  to durationcanvas_ref 129820
  yz 92 2015 explicitmsg "<<create>>"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 139 77
msg 130460 asynchronous
  from durationcanvas_ref 129564
  to durationcanvas_ref 130332
  yz 150 2015 explicitmsg "setDataSource()"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 124 137
msg 130716 synchronous
  from durationcanvas_ref 130332
  to durationcanvas_ref 130588
  yz 166 2015 explicitmsg "<<create>>"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 298 152
msg 130972 synchronous
  from durationcanvas_ref 130588
  to durationcanvas_ref 130844
  yz 173 2020 explicitmsg "<<create>>"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 455 157
msg 131228 synchronous
  from durationcanvas_ref 130332
  to durationcanvas_ref 131100
  yz 203 2015 explicitmsg "<<create>>"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 240 188
msg 131996 synchronous
  from durationcanvas_ref 130332
  to durationcanvas_ref 131868
  yz 243 2015 explicitmsg "setAudioSink()"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 289 228
msg 132252 synchronous
  from durationcanvas_ref 130332
  to durationcanvas_ref 132124
  yz 315 2015 explicitmsg "setDataSource()"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 284 299
msg 132508 synchronous
  from durationcanvas_ref 132124
  to durationcanvas_ref 132380
  yz 320 2020 explicitmsg "setDatasourceAsync()"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 453 304
msg 132764 synchronous
  from durationcanvas_ref 132380
  to durationcanvas_ref 132636
  yz 347 2015 explicitmsg "<<create>>"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 552 329
msg 133020 synchronous
  from durationcanvas_ref 132380
  to durationcanvas_ref 132892
  yz 389 2015 explicitmsg "setDataSource()"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 538 374
reflexivemsg 133276 asynchronous
  to durationcanvas_ref 133148
  yz 418 2025 explicitmsg "kWhatSetDataSource"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 549 427
msg 133532 synchronous
  from durationcanvas_ref 131868
  to durationcanvas_ref 133404
  yz 252 2020 explicitmsg "setAudioSink()"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 446 237
reflexivemsg 133788 asynchronous
  to durationcanvas_ref 133660
  yz 263 2025 explicitmsg "kWhatSetAudioSink"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 552 248
msg 134044 return
  from durationcanvas_ref 133148
  to durationcanvas_ref 132124
  yz 442 2025 unspecifiedmsg
  show_full_operations_definition default drawing_language default show_context_mode default
preferred_whz 1104 632 1.05
end
