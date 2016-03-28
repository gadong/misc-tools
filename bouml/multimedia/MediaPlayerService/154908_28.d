format 75

classinstance 128028 class_ref 129180 // MediaCodec
  name ""   xyz 388.8 21.2 2000 life_line_z 2000
classinstance 128156 class_ref 129308 // ACodec
  name ""   xyz 592.6 23.6 2000 life_line_z 2000
classinstance 128412 class_ref 128924 // NuPlayer::Decoder
  name ""   xyz 171.4 19.2 2000 life_line_z 2000
classinstance 128668 class_ref 143132 // OMX
  name ""   xyz 791 21.4 2000 life_line_z 2000
note 145564 "kWhatInputBufferFilled
kWhatOutputBufferDrained

recollect buffers from ANativeWindow
native_window_dequeue_buffer_and_wait()"
  xyzwh 644 342 2000 271 97
durationcanvas 128796 classinstance_ref 128668 // :OMX
  color mediumyellow
  xyzwh 810 104 2010 11 30
end
durationcanvas 128924 classinstance_ref 128156 // :ACodec
  color magenta
  xyzwh 615 107 2010 11 56
  overlappingdurationcanvas 129180
    color magenta
    xyzwh 621 130 2020 11 27
  end
end
durationcanvas 132764 classinstance_ref 128028 // :MediaCodec
  color magenta
  xyzwh 424 139 2010 11 73
  overlappingdurationcanvas 133020
    color magenta
    xyzwh 430 165 2020 11 39
  end
end
durationcanvas 133276 classinstance_ref 128412 // :NuPlayer::Decoder
  color blue
  xyzwh 224 188 2010 11 555
  overlappingdurationcanvas 133532
    color blue
    xyzwh 230 220 2020 11 284
    overlappingdurationcanvas 134044
      color blue
      xyzwh 236 367 2030 11 129
      overlappingdurationcanvas 134300
	color blue
	xyzwh 242 395 2040 11 95
	overlappingdurationcanvas 134812
	  color blue
	  xyzwh 248 421 2050 11 63
	end
      end
    end
  end
  overlappingdurationcanvas 138780
    color blue
    xyzwh 230 555 2020 11 175
  end
end
durationcanvas 135068 classinstance_ref 128028 // :MediaCodec
  color blue
  xyzwh 424 454 2010 11 38
end
durationcanvas 137116 classinstance_ref 128156 // :ACodec
  color magenta
  xyzwh 615 464 2010 11 64
  overlappingdurationcanvas 137372
    color magenta
    xyzwh 621 477 2020 11 44
  end
end
durationcanvas 137628 classinstance_ref 128668 // :OMX
  color mediumyellow
  xyzwh 810 495 2010 11 26
end
durationcanvas 138012 classinstance_ref 128028 // :MediaCodec
  color blue
  xyzwh 424 248 2010 11 105
  overlappingdurationcanvas 138268
    color magenta
    xyzwh 430 256 2020 11 91
    overlappingdurationcanvas 139420
      color magenta
      xyzwh 436 280 2030 11 55
      overlappingdurationcanvas 139676
	color magenta
	xyzwh 442 305 2040 11 25
      end
    end
  end
end
durationcanvas 139164 classinstance_ref 128028 // :MediaCodec
  color blue
  xyzwh 424 614 2010 11 105
  overlappingdurationcanvas 139932
    color magenta
    xyzwh 430 631 2020 11 79
    overlappingdurationcanvas 140188
      color magenta
      xyzwh 436 648 2030 11 56
      overlappingdurationcanvas 140444
	color magenta
	xyzwh 442 667 2040 11 30
      end
    end
  end
end
durationcanvas 140956 classinstance_ref 128412 // :NuPlayer::Decoder
  color blue
  xyzwh 224 786 2010 11 190
  overlappingdurationcanvas 141340
    color blue
    xyzwh 230 815 2020 11 152
  end
end
durationcanvas 141596 classinstance_ref 128028 // :MediaCodec
  color blue
  xyzwh 424 848 2010 11 123
  overlappingdurationcanvas 141852
    color magenta
    xyzwh 430 861 2020 11 104
    overlappingdurationcanvas 142108
      color magenta
      xyzwh 436 883 2030 11 55
    end
  end
end
durationcanvas 142364 classinstance_ref 128156 // :ACodec
  color magenta
  xyzwh 615 915 2010 11 114
  overlappingdurationcanvas 142620
    color magenta
    xyzwh 621 936 2020 11 87
  end
end
durationcanvas 143132 classinstance_ref 128668 // :OMX
  color mediumyellow
  xyzwh 810 999 2010 11 28
end
durationcanvas 143516 classinstance_ref 128668 // :OMX
  color mediumyellow
  xyzwh 810 1061 2010 11 45
end
durationcanvas 143644 classinstance_ref 128156 // :ACodec
  color magenta
  xyzwh 615 1067 2010 11 74
  overlappingdurationcanvas 143900
    color magenta
    xyzwh 621 1087 2020 11 42
  end
end
durationcanvas 144412 classinstance_ref 128028 // :MediaCodec
  color magenta
  xyzwh 424 1103 2010 11 54
  overlappingdurationcanvas 144668
    color magenta
    xyzwh 430 1124 2020 11 25
  end
end
durationcanvas 144924 classinstance_ref 128412 // :NuPlayer::Decoder
  color blue
  xyzwh 224 1138 2010 11 26
end
lostfoundmsgsupport 140700 xyz 301 586 2025
lostfoundmsgsupport 141084 xyz 294 788 2015
lostfoundmsgsupport 145180 xyz 679 975 2025
msg 129052 asynchronous
  from durationcanvas_ref 128796
  to durationcanvas_ref 128924
  yz 112 2015 explicitmsg "kWhatOMXMessage:EMPTY_BUFFER_DONE"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 628 92
reflexivemsg 129308 synchronous
  to durationcanvas_ref 129180
  yz 130 2025 explicitmsg "postFillBuffer()"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 663 127
msg 132892 asynchronous
  from durationcanvas_ref 129180
  to durationcanvas_ref 132764
  yz 146 2030 explicitmsg "kWhatFillThisBuffer"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 453 131
reflexivemsg 133148 synchronous
  to durationcanvas_ref 133020
  yz 165 2025 explicitmsg "postActivityNotificationIfPossible()"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 458 161
msg 133404 asynchronous
  from durationcanvas_ref 133020
  to durationcanvas_ref 133276
  yz 190 2025 explicitmsg "kWhatCodecNotify"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 262 174
reflexivemsg 133660 synchronous
  to durationcanvas_ref 133532
  yz 220 2025 explicitmsg "handleAnInputBuffer()"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 271 217
reflexivemsg 134172 synchronous
  to durationcanvas_ref 134044
  yz 367 2035 explicitmsg "onRequestInputBuffers()"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 276 364
reflexivemsg 134428 synchronous
  to durationcanvas_ref 134300
  yz 395 2045 explicitmsg "doRequestBuffers()"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 290 394
reflexivemsg 134940 synchronous
  to durationcanvas_ref 134812
  yz 421 3005 explicitmsg "onInputBufferFetched()"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 295 418
msg 135196 synchronous
  from durationcanvas_ref 134812
  to durationcanvas_ref 135068
  yz 454 2055 explicitmsg "queueInputBuffer()"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 302 439
msg 137244 asynchronous
  from durationcanvas_ref 135068
  to durationcanvas_ref 137116
  yz 471 2015 explicitmsg "kWhatInputBufferFilled"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 477 456
reflexivemsg 137500 synchronous
  to durationcanvas_ref 137372
  yz 477 2025 explicitmsg "onInputBufferFilled()"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 654 463
msg 137756 asynchronous
  from durationcanvas_ref 137372
  to durationcanvas_ref 137628
  yz 500 2030 explicitmsg "emptyBuffer()"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 707 484
msg 138140 synchronous
  from durationcanvas_ref 133532
  to durationcanvas_ref 138012
  yz 250 2025 explicitmsg "dequeueInputBuffer"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 275 235
reflexivemsg 138396 asynchronous
  to durationcanvas_ref 138268
  yz 256 2025 explicitmsg "kWhatDequeueInputBuffer"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 462 245
reflexivemsg 138908 synchronous
  to durationcanvas_ref 138780
  yz 555 2025 explicitmsg "handleAnOutputBuffer()"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 271 550
msg 139292 synchronous
  from durationcanvas_ref 138780
  to durationcanvas_ref 139164
  yz 614 2025 explicitmsg "dequeueOutputBuffer()"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 251 600
reflexivemsg 139548 synchronous
  to durationcanvas_ref 139420
  yz 280 2035 explicitmsg "handleDequeueInputBuffer()"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 466 275
reflexivemsg 139804 synchronous
  to durationcanvas_ref 139676
  yz 305 2045 explicitmsg "dequeuePortBuffer()"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 474 302
reflexivemsg 140060 asynchronous
  to durationcanvas_ref 139932
  yz 631 2025 explicitmsg "kWhatDequeueOutputBuffer"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 442 615
reflexivemsg 140316 synchronous
  to durationcanvas_ref 140188
  yz 648 2035 explicitmsg "handleDequeueOutputBuffer()"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 470 643
reflexivemsg 140572 synchronous
  to durationcanvas_ref 140444
  yz 667 2045 explicitmsg "dequeuePortBuffer()"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 470 662
msg 140828 lost_asynchronous
  from durationcanvas_ref 138780
  to lostfoundmsgsupport_ref 140700
  yz 584 2025 explicitmsg "Render::queueBuffer()"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 252 570
msg 141212 found_asynchronous
  from lostfoundmsgsupport_ref 141084
  to durationcanvas_ref 140956
  yz 786 2015 explicitmsg "kWhatRenderBuffer"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 248 768
reflexivemsg 141468 synchronous
  to durationcanvas_ref 141340
  yz 815 2025 explicitmsg "onRenderBuffer"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 265 812
msg 141724 synchronous
  from durationcanvas_ref 141340
  to durationcanvas_ref 141596
  yz 848 2025 unspecifiedmsg
  show_full_operations_definition default drawing_language default show_context_mode default
reflexivemsg 141980 asynchronous
  to durationcanvas_ref 141852
  yz 861 2025 explicitmsg "kWhatReleaseOutputBuffer"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 436 844
reflexivemsg 142236 synchronous
  to durationcanvas_ref 142108
  yz 883 2035 explicitmsg "onReleaseOutputBuffer"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 478 878
msg 142492 asynchronous
  from durationcanvas_ref 142108
  to durationcanvas_ref 142364
  yz 915 2040 explicitmsg "kWhatOutputBufferDrained"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 459 905
reflexivemsg 142748 synchronous
  to durationcanvas_ref 142620
  yz 936 2025 explicitmsg "onOutputBufferDrained"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 639 920
msg 143260 asynchronous
  from durationcanvas_ref 142620
  to durationcanvas_ref 143132
  yz 1000 2025 explicitmsg "fillBuffer()"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 695 985
msg 143772 asynchronous
  from durationcanvas_ref 143516
  to durationcanvas_ref 143644
  yz 1067 2015 explicitmsg "kWhatOMXMessage:FILL_BUFFER_DONE"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 624 1052
reflexivemsg 144028 synchronous
  to durationcanvas_ref 143900
  yz 1087 3005 explicitmsg "onOMXFillBufferDone"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 650 1083
msg 144540 asynchronous
  from durationcanvas_ref 143900
  to durationcanvas_ref 144412
  yz 1108 2025 explicitmsg "kWhatDrainThisBuffer"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 467 1094
reflexivemsg 144796 synchronous
  to durationcanvas_ref 144668
  yz 1124 2025 explicitmsg "postActivityNotificationIfPossible()"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 461 1122
msg 145052 asynchronous
  from durationcanvas_ref 144668
  to durationcanvas_ref 144924
  yz 1138 2025 explicitmsg "kWhatCodecNotify"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 282 1124
msg 145308 lost_synchronous
  from durationcanvas_ref 142620
  to lostfoundmsgsupport_ref 145180
  yz 973 2025 explicitmsg "ANativeWindow::queueBuffer()"
  show_full_operations_definition default drawing_language default show_context_mode default
  label_xy 643 960
end
