$(document).ready(function() {
	// body...
  var numTests=1;
  var fileType={
      zip:"images/zip.png",
      java:"images/java.png",
      cpp:"images/cpp.png",
      c:"images/c.png",
      file:"images/file.png"
  }
  $(".button-add-test-case").on("click",function () {
    numTests++;
    let test=testComponent(numTests);
    $(".test-case-list").append(test);
  });
  $(document).on("change",".checkbox",function() {
    // alert($(this).parent().parent().parent().attr(".test-case"))
      let id=$(this).closest(".test-case").attr("id");
    if ($(this).prop("checked")) {
        $("#"+id+" .not-file-input").css({"visibility":"collapse"})
        $("#"+id+" .file-input").css({"visibility":"visible"})
        $("#"+id+" .dragNdrop").css({"display":"block"})

    } else {
        $("#"+id+" .file-input").css({"visibility":"collapse"})
        $("#"+id+" .not-file-input").css({"visibility":"visible"})
        $("#"+id+" .dragNdrop").css({"display":"none"})

    }
  });
  $(document).on("dragleave drop",".fileInput",function() {
    let parent=$(this).parent().parent();
    console.log(parent.find(".fileMessage").attr("class"));
        parent.find(".fileMessage").css({"display":"block"});
        if (parent.find(".fileSelect").val().indexOf(".")>0) {
          parent.find(".fileIcon").css({"display":"block"});
        }
        parent.find(".placeHolder").css({"display":"none"});

  });
  $(document).on("change",".fileInput",function() {
    let parent=$(this).parent().parent();
      parent.find(".fileMessage").html(parent.find(".fileSelect").val());
      let val=parent.find(".fileSelect").val();
      let array=val.split(".");
      let type=array[array.length-1];
      if (fileType[type]) {
        parent.find(".fileIcon").attr("src",fileType[type]);
      }else{
        parent.find(".fileIcon").attr("src",fileType["file"]);
      }
      parent.find(".fileIcon").css({"display":"block"});

  });
  $(document).on("dragover",".fileInput",function() {
    let parent=$(this).parent().parent();
      parent.find(".fileMessage").css({"display":"none"});
      if (parent.find(".fileSelect").val().indexOf(".")>0) {
        parent.find(".fileIcon").css({"display":"none"});
      }
      parent.find(".placeHolder").css({"display":"block"});

  });
  $(document).on("click",".btn-delete-test-case",function() {
      let mainParent=$(this).closest(".test-case");
      mainParent.remove();
      numTests--;
  });



});
function testComponent(num) {
  let component=`<div class="test-case" id="test-case${num}">
      <div class="test-case-heading">Test Case ${num}</div>
      <table>
          <tbody>
            <tr class="row1 table-row">
                <td class="firstcol">
                   Grade
                </td>
                <td class="lastcol">
                  <select>
                        <option value="20%">20%</option>
                        <option active value="40%">40%</option>
                        <option value="60%">60%</option>
                        <option value="80%">80%</option>
                        <option value="100%">100%</option>
                  </select>
                </td>
            </tr>
            <tr class="table-row">
                <td class="firstcol">
                  Testcase from files
                </td>
                <td class="lastcol">
                  <input type="checkbox" class="checkbox" name="" value="">
                </td>
            </tr>
            <tr class="row2 not-file-input table-row">
                <td class="firstcol">
                   Input
                </td>
                <td class="lastcol">
                   <textarea name="name" rows="8" cols="40"></textarea>
                </td>
            </tr>
            <tr class="row3 not-file-input table-row">
                <td class="firstcol">
                   Output
                </td>
                <td class="lastcol">
                   <textarea name="name" rows="8" cols="40"></textarea>
                </td>
            </tr>
            <tr class="row2 file-input table-row">
                <td class="firstcol">
                   Input File
                </td>
                <td class="lastcol">
                            <div class="mod">
                                <div class="dragNdrop">
                                    <form id="FileUploadForm" method="post" action="public/php/FileUpload.php">
                                        <div class="fileInput" id="fileInput">
                                            <input name="file" id="fileSelect" class="fileSelect" type="file">
                                        </div>
                                    </form>
                                    <img class="placeHolder" src="images/drag.png" alt="dragNdrop">
                                    <img class="fileIcon" src="images/drag.png" alt="dragNdrop">
                                    <div class="fileMessage"><strong>drag & drop<br> or click here</strong>
                                    </div>
                                </div>
                            </div>
                </td>
            </tr>
            <tr class="row3 file-input table-row">
                <td class="firstcol">
                   Output File
                </td>
                <td class="lastcol">
                            <div class="mod">
                                <div class="dragNdrop">
                                    <form id="FileUploadForm" method="post" action="public/php/FileUpload.php">
                                        <div class="fileInput" id="fileInput">
                                            <input name="file" id="fileSelect" class="fileSelect" type="file">
                                        </div>
                                    </form>
                                    <img class="placeHolder" src="images/drag.png" alt="dragNdrop">
                                    <img class="fileIcon" src="images/drag.png" alt="dragNdrop">
                                    <div class="fileMessage"><strong>drag & drop<br> or click here</strong>
                                    </div>
                                </div>
                            </div>
                </td>
            </tr>
          </tbody>
      </table>
    <button style="float: right;" class="btn-delete-test-case">delete</button>
    <div style="clear: both;"></div>

  </div>`;


  return component;
}
