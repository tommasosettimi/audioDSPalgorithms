SampleCounterTS : UGen
{
  *ar {
      ^this.multiNew('audio')
  }

  *kr {
      ^this.multiNew('control')
  }

  name { ^"SampleCounterTS" }


  info { ^"Generated with Faust" }
}

