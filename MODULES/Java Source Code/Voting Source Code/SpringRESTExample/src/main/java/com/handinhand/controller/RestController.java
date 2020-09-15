package com.handinhand.controller;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.Locale;
import java.util.Map;

import javax.servlet.ServletRequest;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.servlet.ModelAndView;

import com.handinhand.model.Parking;
import com.handinhand.model.PrintData;
import com.handinhand.model.Product;
import com.handinhand.model.Shopping;
import com.handinhand.model.Smartbike;
import com.handinhand.model.Stock;
import com.handinhand.model.Transaction;
import com.handinhand.model.User;
import com.handinhand.model.Vote;
import com.handinhand.model.VoterUser;

/**
 * Handles requests for the application home page.
 */
@Controller
public class RestController {

	private static final Logger logger = LoggerFactory.getLogger(RestController.class);


	public RestController() {
	}

	@RequestMapping(value = "/", method = RequestMethod.GET)
	public String home(Locale locale, Model model) {
		System.out.println("Welcome home! The client locale is {}."+locale);

		Date date = new Date();
		DateFormat dateFormat = DateFormat.getDateTimeInstance(DateFormat.LONG, DateFormat.LONG, locale);

		String formattedDate = dateFormat.format(date);

		model.addAttribute("serverTime", formattedDate );

		return "status";
	}




	@RequestMapping(value="/{value}", method=RequestMethod.GET)
	@ResponseBody
	public int insertuser(@PathVariable("value") String Name) {
       MySQLAccess mySQLAccess = new MySQLAccess();
	   int row = 1;
	   VoterUser voterUser = new VoterUser();
	   int status = 0;
	   voterUser.setStatus(1);
	   if(Name.equalsIgnoreCase("a")){
		   status = mySQLAccess.getStatus(1);
		   voterUser.setVoterId(1);
	   }
	   else if(Name.equalsIgnoreCase("b")){
		   status = mySQLAccess.getStatus(2);
		   voterUser.setVoterId(2);
	   }
	   else if(Name.equalsIgnoreCase("c")){
		   status = mySQLAccess.getStatus(3);
		   voterUser.setVoterId(3);
	   }
	   else if(Name.equalsIgnoreCase("d")){
		   status = mySQLAccess.getStatus(4);
		   voterUser.setVoterId(4);
	   }
	   if(status !=2 ) {
		   mySQLAccess.updateVotingUser(voterUser);
	   }


	   return row;
	}

		@RequestMapping(value = "/casteVote", method = RequestMethod.GET)
	  public ModelAndView stock(HttpServletRequest request, HttpServletResponse response) {

		String voterId = request.getParameter("VoterId");
		System.out.println("casteVote----------------"+voterId);
	    ModelAndView mav = new ModelAndView("casteVote");
	    Vote vote = new Vote();
	    vote.setVoterId(Integer.parseInt(voterId));
	    mav.addObject("vote", vote);
	    return mav;
	  }

		@RequestMapping(value = "/Vote1", method = RequestMethod.POST)
		  public ModelAndView vote1(@ModelAttribute("vote") Vote vote) {
			System.out.println("vote----------------"+vote.getVoterId() +"party name=="+vote.getPartName());
			 MySQLAccess mySQLAccess = new MySQLAccess();
			 int previousvote = mySQLAccess.getCandidateCount(vote.getPartName());
			 previousvote = previousvote + 1;
			 mySQLAccess.updateCandidate(previousvote, vote.getPartName());

			 VoterUser voterUser = new VoterUser();
			   voterUser.setStatus(2);
			  voterUser.setVoterId(vote.getVoterId());

			 mySQLAccess.updateVotingUser(voterUser);

		    ModelAndView mav = new ModelAndView("status");
		    return mav;
		  }

		@RequestMapping(value = "/getResults", method = RequestMethod.GET)
		  public ModelAndView getResults(HttpServletRequest request, HttpServletResponse response) {
			MySQLAccess mySQLAccess = new MySQLAccess();
			Map<String,Integer> map = mySQLAccess.getResult();
			 ModelAndView mav = new ModelAndView("results");
			 Map.Entry<String, Integer> minEntry = null;
			 if(map.size() > 0) {
				 for (Map.Entry<String, Integer> entry : map.entrySet()) {

				        if (minEntry == null
				                || entry.getValue().compareTo(minEntry.getValue()) > 0) {
				            minEntry = entry;
				        }
				    }

				 mav.addObject("BJP", map.get("BJP"));
				 mav.addObject("AAP", map.get("AAP"));
				 mav.addObject("CONGRESS", map.get("CONGRESS"));
				 mav.addObject("JDS", map.get("JDS"));
				 mav.addObject("NOTA",map.get("NOTA"));
			 }

		    mav.addObject("winner", minEntry.getKey());
		    return mav;
		  }

		@RequestMapping(value = "/resetVotings", method = RequestMethod.POST)
		  public ModelAndView resetVotings() {
			System.out.println("resetVotings");
			MySQLAccess mySQLAccess = new MySQLAccess();
			mySQLAccess.updateAllVotingUser();
			mySQLAccess.updateAllPartyCOunt();
			 ModelAndView mav = new ModelAndView("status");
			 return mav;
		  }


}
