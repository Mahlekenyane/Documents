$(document).ready(function() {
	// body...
  var myDiv = document.getElementById("fileInput");
  myDiv.ondragover = dragOver;
  myDiv.ondragleave = dragLeave;
  myDiv.ondrop = dragLeave;
  myDiv.onchange = dragDrop;
  var fileType={
	zip:"images/zip.png",
	java:"images/java.png",
	cpp:"images/cpp.png",
	c:"images/c.png",
	jar:"images/jar.png",
	m:"images/m.png",
	py:"images/py.png",
	file:"images/file.png"
  }

    $(".mod .upload-submit").on("click",function() {
		$("#FileUploadForm").submit();
    });

    $(".mod .upload-cancel").on("click",function() {
      $(".fileSelect").val("")
      $(".mod .fileMessage").html("<strong>drag & drop<br> or click here</strong>");
      $(".mod .fileIcon").css({"display":"none"});
      $(".mod").css({"display":"none"});
      // alert($(".fileSelect").val())
    });

    $(".upload-file-button").on("click",function() {
      $(".mod").css({"display":"block"});
    });

  function dragOver(){
      $(".mod .fileMessage").css({"display":"none"});
      if ($(".fileSelect").val().indexOf(".")>0) {
        $(".mod .fileIcon").css({"display":"none"});
      }
      $(".mod .placeHolder").css({"display":"block"});
  }
  function dragLeave(){
      $(".mod .fileMessage").css({"display":"block"});
      if ($(".fileSelect").val().indexOf(".")>0) {
        $(".mod .fileIcon").css({"display":"block"});
      }
      $(".mod .placeHolder").css({"display":"none"});
      // alert("J")
  }
  function dragDrop(){
      $(".mod .fileMessage").html($(".fileSelect").val());
      let val=$(".fileSelect").val();
      let array=val.split(".");
      let type=array[array.length-1];
      if (fileType[type]) {
        $(".mod .fileIcon").attr("src",fileType[type]);
      }else{
        $(".mod .fileIcon").attr("src",fileType["file"]);
      }
      $(".mod .fileIcon").css({"display":"block"});
  }




});
