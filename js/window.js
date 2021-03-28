chrome.tabs.query({active: true, lastFocusedWindow: true}, tabs => {
  let url = tabs[0].url;
  // use `url` here inside the callback because it's asynchronous!
  if(!url.includes("/dp/")  && !url.includes("amazon")){
    let score = document.getElementById("review_score")
    score.innerHTML = "Currently not on a product"

    let report_card = document.getElementById("report_card")
    report_card.style.display = "none"
  }
  else {
    let base_reviewmeta_url = "https://reviewmeta.com/api/amazon/"
    let split_url = url.split('/');
    let final_url = base_reviewmeta_url + split_url[5]

    let score = document.getElementById("review_score")

    fetch(final_url).then(response => response.json()).then((out) => {
      score.innerHTML = out.rating
      document.getElementById("report_card").setAttribute("href", out.href)
    })
  }
});