// 페이지가 로드될 때 초기 설정
document.addEventListener('DOMContentLoaded', function() {
    // 로컬 스토리지에서 저장된 이미지 상태 가져오기
    var imageType = localStorage.getItem('imageType');
  
    // 만약 저장된 값이 없으면 기본으로 'deactivation'으로 설정
    imageType = imageType || 'deactivation';
  
    // 이미지 및 버튼 상태 설정
    setImagesAndButtons(imageType);
  });
  
  // 이미지 및 버튼 상태를 설정하는 함수
  function setImagesAndButtons(imageType) {
    let activationImage = document.getElementById('activationImage');
    let deactivationImage = document.getElementById('deactivationImage');
    let runButton = document.querySelector('.run-button');
    let stopButton = document.querySelector('.stop-button');
  // 여기까지 버튼과 이미지 초기 설정
    if (imageType === 'activation') {             // image가 활성화 상태일 때
      activationImage.style.display = 'block';    // 감지 모드 영상(이미지) 소스를 활성화
      deactivationImage.style.display = 'none';   // 비감지 모드 영상(이미지) 소스를 비 활성화
      runButton.classList.add('active');          // run button style 활성화
      stopButton.classList.remove('active');      // stop button style 비 활성화
    } else if (imageType === 'deactivation') {    // image가 비활성화 상태일 때 --> 아래 내용은 위에 내용과 반대)
      activationImage.style.display = 'none';
      deactivationImage.style.display = 'block';
      runButton.classList.remove('active');
      stopButton.classList.add('active');
    }
  
    // 로컬 스토리지에 현재 이미지 상태 저장
    localStorage.setItem('imageType', imageType);
  }
  
  // 이미지 전환 함수
  function toggleImages(imageType) {
    setImagesAndButtons(imageType);
  }
  