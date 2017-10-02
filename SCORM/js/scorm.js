$(document).ready(function() {
	var assignment_id = "10";
	var learner_id = "5";
	$.ajax({
		url: "http://165.165.131.69/getdata.php?id="+assignment_id,
		data: {
			//post data to the server
		},
		cache: false,
		method: "get",
		success: function(response){
			//make use of the response
			if (response) {
				try {
					let table=JSON.parse(response);
					$("#assignment_onlinejudge_information .r0 .c1").html(table[0].language);
					$("#assignment_onlinejudge_information .r1 .c1").html(table[0].size);
					$("#assignment_onlinejudge_information .r2 .c1").html(table[0].time + " sec");
					$(".instructions").html(table[0].instructions);
				} catch (e) {
					console.log(e);
				}
			}
		}
	});
	results();

	$('#FileUploadForm').submit(function(e) {
		e.preventDefault();
		$(".results").css("display","none");
		$(".marker-holder .loader-holder").css({"display":"block"});
		$("#learner_id").val(learner_id);
		$("#assignment_id").val(assignment_id);
		var data = new FormData(this);
		$.ajax({
			url : "http://165.165.131.69/gen.php",
			type: "POST",
			data : data,
			processData: false,
			contentType: false,
			success:function(response, textStatus, jqXHR) {
				results();
			},
			error: function(jqXHR, textStatus, errorThrown) {
				alert("error!!!!!!!!!!!!!!");
			}
		});
		$("#fileCancel").trigger("click");
	});
});


function results() {
	$.ajax({
	url: "http://165.165.131.69/get_sub.php",
	data: {
		learner_id:"5", //learner id
		ass_id:"10"
	},
	cache: false,
	method: "get",
	success: function(response){
		//make use of the response
		if (response) {
			try {
				let table=JSON.parse(response);
				let d=new Date(table[0].sub_time);
			    var dayOfWeek={
			      1:"Monday",
			      2:"Tuesday",
			      3:"Wednesday",
			      4:"Thursday",
			      5:"Friday",
			      6:"Saturday",
			      0:"Sunday"
			    }
			    var Month={
				  0:"January",
			      1:"February",
			      2:"March",
			      3:"April",
			      4:"May",
			      5:"June",
			      6:"July",
			      7:"August",
			      8:"September",
			      9:"October",
			      10:"November",
			      11:"December",
			    }
				let Hours=""+d.getHours();
				if (Hours.length==1) {
					//alert(Hours.length);
					Hours="0"+Hours;
				}
				let Minutes=""+d.getMinutes();
				if (Minutes.length==1) {
					Minutes="0"+Minutes;
				}
				let date=dayOfWeek[d.getDay()]+", "+d.getDate()+" "+Month[d.getMonth()]+" "+d.getFullYear()+" "+Hours+":"+Minutes;
				$("#assignment_onlinejudge_summary .r0 .c1 span").html(table[0].status).removeClass("notifysuccess").removeClass("notifyfailure");
				if (table[0].status=="Accepted") {
					$("#assignment_onlinejudge_summary .r0 .c1 span").addClass("notifysuccess");
				}else{
					$("#assignment_onlinejudge_summary .r0 .c1 span").addClass("notifyfailure");
				}
				$("#assignment_onlinejudge_summary .r1 .c1").html(date);

				$(".marker-holder .results .my-grade").html(table[0].grade);

				let test=table[0].grade_json.split(",");
				let testCaseContainer=$("#assignment_onlinejudge_summary .r2 .c1 .text_to_html")
				testCaseContainer.html("");
				for (var i = 0; i < test.length; i++) {
					if(test[i] !== "")
						testCaseContainer.append(test[i]+"<br>");
				}

				let path=table[0].path;
				let nameArr=table[0].path.split("/");
				let name=nameArr[nameArr.length-1];
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
				let array=name.split(".");
		        let type=array[array.length-1];

		        if (fileType[type]) {
		          $(".results .upload-link img").attr("src",fileType[type]);
		        }else{
		          $(".results .upload-link img").attr("src",fileType["file"]);
		        }
		          $(".results .upload-link").attr("href",path);
  		          $(".results .upload-link div").html(name);
				// alert(name);



				$(".marker-holder .loader-holder").css({"display":"none"});
				$(".results").css("display","block");
			} catch (e) {
				console.log(e);
			}
		}

	}
});
}
